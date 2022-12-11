#include "worldcup23a1.h"
#include <math.h>

world_cup_t::world_cup_t()
{
    m_all_teams = AvlTree<team, int>();
    m_allowed_to_play_teams = AvlTree<team, int>();
    m_all_players_id = AvlTree<player, int>();
    m_all_players_goals = AvlTree<player, playerStats>();
    m_top_scorer = nullptr;
    m_total_players = 0;
    m_num_teams = 0;
    m_num_eligible_to_play_teams = 0;
}

world_cup_t::~world_cup_t()
{
    m_all_teams.deleteTree(m_all_teams.getRoot());
    m_all_players_goals.deleteTree(m_all_players_goals.getRoot());
    m_allowed_to_play_teams.deleteTree(m_allowed_to_play_teams.getRoot());
    m_all_players_id.deleteTree(m_all_players_id.getRoot());
    delete m_top_scorer;
}

void mergeArrays(playerStats* arr1[], playerStats* arr2[], int m, int n, playerStats* arr3[]){
    int i = 0;
    int j = 0;
    int k = 0;
    //Traverse both arrays
    while (i<m && j<n){
        //check if current element of first
        //array is smaller than current element
        //of second array. if yes, store first
        //array element and increment first array
        //index. Otherwise, do same with second array
        if(arr1[i] < arr2[j]){
            arr3[k++] = arr1[i++];
        }
        else{
            arr3[k++] = arr2[j++];
        }
    }
}

void mergeArrays(player* arr1[], player* arr2[], int m, int n, player* arr3[]){
    int i = 0;
    int j = 0;
    int k = 0;
    //Traverse both arrays
    while (i<m && j<n){
        //check if current element of first
        //array is smaller than current element
        //of second array. if yes, store first
        //array element and increment first array
        //index. Otherwise, do same with second array
        if(arr1[i] < arr2[j]){
            arr3[k++] = arr1[i++];
        }
        else{
            arr3[k++] = arr2[j++];
        }
    }
}


//working!
StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId <= 0 || points < 0){
        return StatusType::INVALID_INPUT;
    }
    team* tmp = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(tmp != nullptr){
        tmp=nullptr;
        return StatusType::FAILURE;
    }

    team team1 = team(teamId, points);
    m_all_teams.insert(m_all_teams.getRoot(),&team1, teamId);
    tmp = nullptr;
    m_num_teams++;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    team* team1 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(team1 == nullptr){
        return StatusType::FAILURE;
    }
    if(team1->getNumPlayers()){
        team1 = nullptr;
        return StatusType::FAILURE;
    }
    else{
        m_all_teams.remove(m_all_teams.getRoot(),teamId);
        if(team1->isTeamValid()){
            m_allowed_to_play_teams.remove(m_allowed_to_play_teams.getRoot(),teamId);
            m_num_eligible_to_play_teams--;
        }
        team1 = nullptr;
        m_num_teams--;
        return StatusType::SUCCESS;
    }
}
//working!
StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if(playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 ||
       cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0))){
        return StatusType::INVALID_INPUT;
    }
    player* tmp_player = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);
    // player already exist
    if(tmp_player != nullptr){
        tmp_player = nullptr;
        return StatusType::FAILURE;
    }
    //delete tmp_player;
    // team does not exist
    team* tmp_team = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(tmp_team == nullptr){
        tmp_team = nullptr;
        return StatusType::FAILURE;
    }
    try {
        m_total_players++;
        player newPlayer = player(playerId,teamId,tmp_team,gamesPlayed,goals,cards,goalKeeper);

        //newPlayer.addNewPlayer(playerId,tmp_team,gamesPlayed,goals,cards,goalKeeper);
        playerStats newPlayerStats = newPlayer.getMyStats();
        if(m_top_scorer == nullptr){
            m_top_scorer = &newPlayer;
        }
        else if(m_top_scorer->getMyStats() < newPlayerStats){
            m_top_scorer = &newPlayer;
        }
        tmp_team->addPlayer(&newPlayer,newPlayerStats,playerId);
        //std::cout<< "here";

        m_all_players_goals.insert(m_all_players_goals.getRoot(),&newPlayer,newPlayerStats);
        m_all_players_id.insert(m_all_players_id.getRoot(),&newPlayer,playerId);
        if(newPlayerStats > tmp_team->getTopScorerStats()){
            tmp_team->setTopScorer(&newPlayer);
        }
        player* pre = nullptr;
        player* suc = nullptr;
        m_all_players_goals.successorPredecessor(m_all_players_goals.getRoot(),newPlayerStats,pre,suc);
        newPlayer.setPre(pre);
        newPlayer.setSuc(suc);
        newPlayer.setClosest(newPlayer.closestOfTwo(pre,suc));
        //changing pre and suc closest if needed
        if(pre != nullptr){
            pre->setClosest(pre->closestOfTwo(pre->getClosest(),&newPlayer));
        }
        if(suc != nullptr){
            (*suc).setClosest((*suc).closestOfTwo(suc->getClosest(),&newPlayer));
        }
        //check if team is allowed to play
        if((*tmp_team).isTeamValid()){
            if(m_allowed_to_play_teams.find_by_key(m_allowed_to_play_teams.getRoot(),teamId)==nullptr) {
                m_allowed_to_play_teams.insert(m_allowed_to_play_teams.getRoot(), tmp_team, teamId);
                m_num_eligible_to_play_teams++;
            }
        }
        //std::cout<<newPlayer.totalGames();
        //delete tmp_team;
    } catch (std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

void world_cup_t::fixClosest(player *changePlayer) {
    class player* pre1;
    class player* suc1;
    m_all_players_goals.successorPredecessor(m_all_players_goals.getRoot(),changePlayer->getMyStats(),pre1,suc1);
    changePlayer->setPre(pre1);
    changePlayer->setSuc(suc1);
    changePlayer->setClosest(changePlayer->closestOfTwo(pre1,suc1));
}


StatusType world_cup_t::remove_player(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    player* playerToDelete = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);
    if(playerToDelete == nullptr){
        delete playerToDelete;
        return StatusType::FAILURE;
    }

    team* tmp = playerToDelete->getMyTeam();
    player* pre=playerToDelete->getPre();
    player* suc=playerToDelete->getSuc();


    //if team is not valid to play anymore - remove from tree and update the num of valid teams:
    (*tmp).removePlayer((*playerToDelete).getMyStats(),playerId);
    if(!tmp->isTeamValid()){
        if(m_allowed_to_play_teams.find_by_key(m_allowed_to_play_teams.getRoot(),tmp->getId())) {
            m_allowed_to_play_teams.remove(m_allowed_to_play_teams.getRoot(),tmp->getId());
            m_num_eligible_to_play_teams--;
        }
    }


    if(playerToDelete == tmp->getTopScorer()){
        tmp->setTopScorer(tmp->getTopNewScorer());
    }

    //remove player from other trees:
    m_all_players_id.remove(m_all_players_id.getRoot(),playerId);
    m_all_players_goals.remove(m_all_players_goals.getRoot(),(*playerToDelete).getMyStats());
    // m_all_players_different_order.remove(m_all_players_different_order.getRoot(),(*playerToDelete).getDiffStats()); // add this helper func

    if(playerToDelete == m_top_scorer){
        m_top_scorer = m_all_players_goals.getBiggest(m_all_players_goals.getRoot());
    }

    //fix deleted players pre and suc closest:
    if(pre->getClosest()==playerToDelete){
        fixClosest(pre);
    }
    if(suc->getClosest()==playerToDelete){
        fixClosest(suc);
    }

    delete tmp;
    delete pre;
    delete suc;
    delete playerToDelete;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived)
{
    if(playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0){
        return StatusType::INVALID_INPUT;
    }
    ///to do: see how to handle bad alloc
    /*  auto* tmp_player = new player;
      if(!tmp_player){
          delete tmp_player;
          return StatusType::ALLOCATION_ERROR;
      }*/

    player* tmp_player = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);
    if(tmp_player == nullptr){
        return StatusType::FAILURE;
    }

    team* tmp_team = m_all_teams.find_by_key(m_all_teams.getRoot(),tmp_player->getTeamId());
    if(tmp_team == nullptr){
        return StatusType::FAILURE;
    }
   // if(tmp_team == nullptr) {
 /*   if(tmp_team == NULL) {
        delete tmp_team;
        return StatusType::FAILURE;
    }*/ //at this point if the player exists the group does too.

    // remove player with old stats
    m_all_players_goals.remove(m_all_players_goals.getRoot(),tmp_player->getMyStats());
    //std::cout<<'3';
    tmp_team->removePlayer(tmp_player->getMyStats(),playerId);

    // add player with new stats
    tmp_player->addCards(cardsReceived);
    tmp_player->addGames(gamesPlayed);
    tmp_player->addGoals(scoredGoals);
    tmp_player->updateStats();
    m_all_players_goals.insert(m_all_players_goals.getRoot(),tmp_player,tmp_player->getMyStats());
    tmp_team->addPlayer(tmp_player,tmp_player->getMyStats(),playerId);



    if(tmp_player == m_all_players_goals.getBiggest(m_all_players_goals.getRoot())){
        m_top_scorer = tmp_player;
    }



    if(tmp_player == tmp_team->getTopNewScorer()){
        tmp_team->setTopScorer(tmp_player);
    }


    //change old player pre and suc:
    player* oldPre=tmp_player->getPre();
    player* oldSuc=tmp_player->getSuc();
    if(oldPre->getClosest()==tmp_player){
        fixClosest(oldPre);
    }
    if(oldSuc->getClosest()==tmp_player){
        fixClosest(oldSuc);
    }

    //update player's pre+suc and closest:
    fixClosest(tmp_player);

    //update new stats' player's pre and suc:
    player* newPre=tmp_player->getPre();
    player* newSuc=tmp_player->getSuc();
    fixClosest(newPre);
    fixClosest(newSuc);


    delete tmp_player;
    delete tmp_team;
    delete oldPre;
    delete oldSuc;
    delete newPre;
    delete newSuc;

    return StatusType::SUCCESS;
}

//working!
StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    team* team1 = m_allowed_to_play_teams.find_by_key(m_allowed_to_play_teams.getRoot(),teamId1);
    team* team2 = m_allowed_to_play_teams.find_by_key(m_allowed_to_play_teams.getRoot(),teamId2);
    if(team1 == nullptr || team2 == nullptr){
        team1 = nullptr;
        team2 = nullptr;
        return StatusType::FAILURE;
    }
    int sum1 = team1->getNumPoints() + team1->getNumGoals() - team1->getNumCards();
    int sum2 = team2->getNumPoints() + team2->getNumGoals() - team2->getNumCards();
    if(sum1 > sum2){
        team1->updatePoints(3);
        team1->addGamePlayed();
        team2->addGamePlayed();
    }
    else if(sum2>sum1){
        team2->updatePoints(3);
        team1->addGamePlayed();
        team2->addGamePlayed();
    }
    else{
        team1->updatePoints(1);
        team2->updatePoints(1);
        team1->addGamePlayed();
        team2->addGamePlayed();
    }
    team1 = nullptr;
    team2 = nullptr;
    return StatusType::SUCCESS;
}
//returns wrong number somehow
output_t<int> world_cup_t::get_num_played_games(int playerId)
{

    if(playerId <= 0){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    //todo: see how to handle bad alloc
    /* player* player1 = new player*; ///alloc?
     if(!player1){
         delete player1;
         output_t<int> out(StatusType::ALLOCATION_ERROR);
         return out;
     }*/

    player* player1 = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);//returns null if haven't found
    if(player1 == nullptr){
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
   // std::cout<<player1->getTeamId();
    output_t<int> out(player1->totalGames());
    player1 = nullptr;
    return out;
}

//returns wrong number maybe we have a problem with the way we change memory? I'll think about it tomorrow, it's getting super late
output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }

    ///to do: see how to handle bad alloc
    //these two might throw exceptions
/*    wanted_team = new team;
    team* wanted_team = new team; ///alloc??
    if(!wanted_team){
        output_t<int> out(StatusType::ALLOCATION_ERROR); //fix
        delete wanted_team;
        return out;
    }*/

    team* wanted_team = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(wanted_team == nullptr){
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
    output_t<int> out(wanted_team->getNumPoints());
    wanted_team = nullptr;
    return out;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(newTeamId <= 0 || teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }

    team* team1=m_all_teams.find_by_key(m_all_teams.getRoot(),teamId1);
    team* team2=m_all_teams.find_by_key(m_all_teams.getRoot(),teamId2);
/*
    node<player,playerStats>* arr1[team1->getNumPlayers()];
    node<player,playerStats>* arr2[team2->getNumPlayers()];
    node<player,playerStats>* mergedArr[team2->getNumPlayers()+team1->getNumPlayers()];

    team1->getArrayStats(arr1);
    team2->getArrayStats(arr2);
    */
//////////////////////////////////////////////////// maybe?
    player** arrT1 = new player*[team1->getNumPlayers()];
    playerStats** arrK1 = new playerStats*[team1->getNumPlayers()];
    team1->storeTree(arrT1,arrK1);
    player** arrT2 = new player*[team2->getNumPlayers()];
    playerStats** arrK2 = new playerStats*[team2->getNumPlayers()];
    team2->storeTree(arrT2,arrK2);
    player** mergedPlayer = new player*[team1->getNumPlayers()+team2->getNumPlayers()];
    playerStats** mergedKeys = new playerStats*[team1->getNumPlayers()+team2->getNumPlayers()];
    mergeArrays(arrT1,arrT2,team1->getNumPlayers(),team2->getNumPlayers(),mergedPlayer);
    mergeArrays(arrK1,arrK2,team1->getNumPlayers(),team2->getNumPlayers(),mergedKeys);
    team newTeam=team(newTeamId,team1->getNumPoints()+team2->getNumPoints());
    for (int player = 0; player < (team1->getNumPlayers()+team2->getNumPlayers()); player++){
        mergedPlayer[player]->setMyTeam(&newTeam);
    }
    AvlTree<player, playerStats> unitedNewTree;
    unitedNewTree.setRoot(unitedNewTree.mergeTrees(mergedPlayer,mergedKeys,team1->getNumPlayers(),team2->getNumPlayers()));
    newTeam.setTeamTree(unitedNewTree);
////////////////////////////////////////////////////
    /*
    mergeArrays(arr1,arr2,team1->getNumPlayers(),team2->getNumPlayers(),mergedArr);


    for (int player = 0; player < newTeam.getNumPlayers(); player++){
        mergedArr[player]->data.setMyTeam(&newTeam);
    }


    int height=((int)log2(team2->getNumPlayers()+team1->getNumPlayers()+1))-1;
    AvlTree<player,playerStats> unitedTree=AvlTree<player,playerStats>();
    node<player, playerStats>* root= unitedTree.getRoot();
    unitedTree.createEmptyTree(root,height);
    unitedTree.setRoot(root);
    int toDelete= pow(2,height)-(team2->getNumPlayers()+team1->getNumPlayers());
    unitedTree.makeNearlyEmpty(root, &toDelete);
    unitedTree.arrayToBST(root,mergedArr);


    newTeam.setTeamTree(unitedTree);
    */

    m_all_teams.insert(m_all_teams.getRoot(),&newTeam,newTeamId);
    if(newTeam.isTeamValid()){
        m_allowed_to_play_teams.insert(m_allowed_to_play_teams.getRoot(),&newTeam,newTeamId);
    }
    team1->deleteTeam();
    team2->deleteTeam();
    remove_team(teamId1);
    remove_team(teamId2);
    return StatusType::SUCCESS;
}
//once again wrong number somehow :|
output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId == 0){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    else if(teamId < 0){
        if(m_total_players <= 0){
            output_t<int> out(StatusType::FAILURE);
            return out;
        }
        output_t<int> out(m_top_scorer->getId());
        return out;
    }
    else{
        ///to do: see how to handle bad alloc
        /*team* team1 = new team; //fix
        if(!team1){
            output_t<int> out(StatusType::ALLOCATION_ERROR);
            delete team1;
            return out;
        }*/
        team* team1 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);//returns null if the team hasn't found
        if(team1 == nullptr){
            output_t<int> out(StatusType::FAILURE);
            return out;
        }
        output_t<int> out(team1->top_scorer_id());
        team1 = nullptr;
        return out;
    }
}
//updated out
output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId == 0){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    else if (teamId < 0){
        output_t<int> out(m_total_players);
        return out;
    }
    else{
        ///to do: see how to handle bad alloc
        /*team* team1 = new team; //fix
        if(team1 == NULL){
            output_t<int> out(StatusType::ALLOCATION_ERROR);
            delete team1;
            return out;
        }*/
        team* team1 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
        if(team1 == nullptr){
            output_t<int> out(StatusType::FAILURE);
            return out;
        }
        output_t<int> out(team1->getNumPlayers());
        team1 = nullptr;
        return out;
    }
}
//updated
StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if(teamId == 0 || output == nullptr){
        return StatusType::INVALID_INPUT;
    }
    if(teamId > 0) {
        ///to do: see how to handle bad alloc
        /*team *tmp_team = new team;//??
        if (tmp_team == NULL) {
            delete tmp_team;
            return StatusType::ALLOCATION_ERROR;
        }*/

        team *tmp_team = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
        if (tmp_team == nullptr) {
            delete tmp_team;
            return StatusType::FAILURE;
        }
        tmp_team->getArrayId(output);
        delete tmp_team;
    }
    else
        m_all_players_goals.storeInOrderRecursiveKey(m_all_players_goals.getRoot(), output);
    return StatusType::SUCCESS;
}

//updated out
output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if(playerId <= 0 || teamId <= 0){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    team* team1 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(team1 == nullptr){
        delete team1;
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
    player* player1 = team1->findPlayerById(playerId);
    delete team1;
    if(player1 == nullptr){
        delete player1;
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
    output_t<int> out(player1->getClosest()->getId());
    delete player1;
    return out;
}
//updated!!
output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    try {
        team** arr_team = nullptr;
        arr_team = new team*[m_num_eligible_to_play_teams];
        for(int i = 0; i < m_num_eligible_to_play_teams; i++){
            arr_team[i] = nullptr;
        }
        //////////////////////////////////////////////////////// maybe?
        int i=0;
        m_allowed_to_play_teams.storeInorderTerms(minTeamId,maxTeamId,m_allowed_to_play_teams.getRoot(),arr_team,&i);
        //m_allowed_to_play_teams.storeInOrderRecursiveByTerms(minTeamId,maxTeamId,m_allowed_to_play_teams.getRoot(),arr_team);//probably need to implement in avltree unless there is a better soultion
        ///////////////////////////////////////////////////////
        AvlTree<team, int> knock_out_tree;
        int num_eligible_in_terms_teams = 0;
        for(int i = 0; i < m_num_eligible_to_play_teams; i++){
            if(arr_team[i] != nullptr){
                knock_out_tree.insert(knock_out_tree.getRoot(), arr_team[i], arr_team[i]->getId());
                num_eligible_in_terms_teams++;
            }
            else{
                break;
            }
        }
        if(!m_num_eligible_to_play_teams){
            output_t<int> out(StatusType::FAILURE);
            delete[] arr_team;
            return out;
        }
        int playing_teams = num_eligible_in_terms_teams;
        while(playing_teams > 1){
            for(int curr_team = 0; curr_team < playing_teams-1; curr_team += 2){
                while (arr_team[curr_team] == nullptr && curr_team < playing_teams-1){
                    curr_team++;
                }
                int first_team = curr_team;
                while (arr_team[curr_team+1] == nullptr && curr_team + 1 < playing_teams){
                    curr_team++;
                }
                int second_team = curr_team+1;
                int team1_points = arr_team[first_team]->getNumPoints(),
                        team2_points = arr_team[second_team]->getNumPoints();
                int team1_id = arr_team[first_team]->getId(),
                        team2_id = arr_team[second_team]->getId();
                play_match(team1_id, team2_id);
                int curr_points_team1 = arr_team[first_team]->getNumPoints(),
                        curr_points_team2 = arr_team[second_team]->getNumPoints();
                if(team1_points + 3 == curr_points_team1 && team2_points == curr_points_team2){
                    unite_teams(team1_id, team2_id, team1_id);
                    arr_team[second_team] = nullptr;//maybe need to create new array each while iteration in size/2
                    playing_teams--;//or put a for that take the next eligible team for the game? I think that's better
                    continue;
                }
                else if(team2_points + 3 == curr_points_team2 && team1_points == curr_points_team1){
                    unite_teams(team1_id, team2_id, team2_id);
                    arr_team[first_team] = nullptr;
                    playing_teams--;
                    continue;
                }
                else if(team1_points + 1 == curr_points_team1 && team2_points + 1 == curr_points_team2){
                    if(team1_id > team2_id) {
                        unite_teams(team1_id, team2_id, team1_id);
                        playing_teams--;
                        arr_team[second_team] = nullptr;
                        arr_team[first_team]->updatePoints(2);
                        continue;
                    }
                    else if(team2_id > team1_id){
                        unite_teams(team1_id, team2_id, team2_id);
                        playing_teams--;
                        arr_team[first_team] = nullptr;
                        arr_team[second_team]->updatePoints(2);
                        continue;
                    }
                    else{
                        output_t<int> out(StatusType::FAILURE);
                        delete[] arr_team;
                        return out;
                    }
                }
                else{
                    output_t<int> out(StatusType::FAILURE);
                    delete[] arr_team;
                    return out;
                }
            }

        }
        int winner;
        for (int curr = 0; curr < num_eligible_in_terms_teams; curr++){
            if(arr_team[curr] != nullptr){
                winner = arr_team[curr]->getId();
                break;
            }
        }
        delete[] arr_team;
        output_t<int> out(winner);
        return out;
    }
    catch (std::exception& e) {
        output_t<int> out(StatusType::ALLOCATION_ERROR);
        return out;
    }
}


