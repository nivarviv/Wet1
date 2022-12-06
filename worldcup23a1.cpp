#include "worldcup23a1.h"
#include <math.h>

world_cup_t::world_cup_t()
{
    m_all_teams = AvlTree<team, int>();
    m_allowed_to_play_teams = AvlTree<team, int>();
    m_all_players_id = AvlTree<player, int>();
    m_all_players_goals = AvlTree<player, playerStats>();
    m_all_players_different_order=AvlTree<player,playerStatsDifferentOrder>();
    m_top_scorer = NULL;
    m_total_players = 0;
    m_num_teams = 0;
    m_num_eligible_to_play_teams = 0;
}
//updated
world_cup_t::~world_cup_t()
{
    delete m_top_scorer;
}

//updated
StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId <= 0 || points < 0){
        return StatusType::INVALID_INPUT;
    }
    team* tmp = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(tmp == NULL){//it returns null if we haven't found such team
        delete tmp;
        return StatusType::FAILURE;
    }
    team team1 = team(teamId, points);
    //check for exception
    m_all_teams.insert(m_all_teams.getRoot(),team1, teamId);
    delete tmp;
    m_num_teams++;
	return StatusType::SUCCESS;
}
//updated
StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    team* team1 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(!team1){
        delete team1;
        return StatusType::FAILURE;
    }
    if((*team1).getNumPlayers()){ // meant not (!) ?
        delete team1;
        return StatusType::FAILURE;
    }
    else{
        m_all_teams.remove(m_all_teams.getRoot(),teamId);
        delete team1;
        m_num_teams--;
        return StatusType::SUCCESS;
    }
}


//updated
StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if(playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 ||
        cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0))){
        return StatusType::INVALID_INPUT;
    }
    player* tmp_player = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);
    // player already exist
    if(tmp_player != NULL){
        delete tmp_player;
        return StatusType::FAILURE;
    }
    delete tmp_player;
    // team does not exist
    team* tmp_team = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
    if(tmp_team == NULL){
        delete tmp_team;
        return StatusType::FAILURE;
    }
    try {
        m_total_players++;
        player newPlayer;
        newPlayer.addNewPlayer(playerId,tmp_team,gamesPlayed,goals,cards,goalKeeper);
        playerStats newPlayerStats= newPlayer.getMyStats();
        playerStatsDifferentOrder newPlayerDiffStats = newPlayer.getDiffStats(); //add this helper function

        (*tmp_team).addPlayer(&newPlayer,newPlayerStats,playerId);
        m_all_players_goals.insert(m_all_players_goals.getRoot(),newPlayer,newPlayerStats);
        m_all_players_id.insert(m_all_players_id.getRoot(),newPlayer,playerId);
        m_all_players_different_order.insert(m_all_players_different_order.getRoot(),newPlayer,newPlayerDiffStats);

        player* pre;
        player* suc;
        m_all_players_goals.successorPredecessor(m_all_players_goals.getRoot(),newPlayerStats,pre,suc);
        newPlayer.setPre(pre);
        newPlayer.setSuc(suc);
        newPlayer.setClosest(newPlayer.closestOfTwo(pre,suc));

        //changing pre and suc closest if needed
        (*pre).setClosest((*pre).closestOfTwo(pre->getClosest(),&newPlayer));
        (*suc).setClosest((*suc).closestOfTwo(suc->getClosest(),&newPlayer));
        m_num_teams++;
        //check if team is allowed to play
        if((*tmp_team).isTeamValid()){
            if(m_allowed_to_play_teams.find_by_key(m_allowed_to_play_teams.getRoot(),teamId)==NULL) {
                m_allowed_to_play_teams.insert(m_allowed_to_play_teams.getRoot(), (*tmp_team), teamId);
                m_num_eligible_to_play_teams++;
            }
        }
        delete tmp_team;
    } catch (std::exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}


void world_cup_t::fixClosest(player *player) { //fix here?
    class player* pre1;
    class player* suc1;
    m_all_players_goals.successorPredecessor(m_all_players_goals.getRoot(),player->getMyStats(),pre1,suc1);
    (*player).setPre(pre1);
    (*player).setSuc(suc1);
    (*player).setClosest((*player).closestOfTwo(pre1,suc1));
}

//todo:
StatusType world_cup_t::remove_player(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    player* playerToDelete = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);
    if(playerToDelete == NULL){
        delete playerToDelete;
        return StatusType::FAILURE;
    }
    team* tmp = playerToDelete->getMyTeam();
    player* pre=playerToDelete->getPre();
    player* suc=playerToDelete->getSuc();
    if(pre->getClosest()==playerToDelete){
        fixClosest(pre);
    }
    if(suc->getClosest()==playerToDelete){
        fixClosest(suc);
    }
    (*tmp).removePlayer((*playerToDelete).getMyStats(),playerId);
    m_all_players_id.remove(m_all_players_id.getRoot(),playerId);
    m_all_players_goals.remove(m_all_players_goals.getRoot(),(*playerToDelete).getMyStats());
    m_all_players_different_order.remove(m_all_players_different_order.getRoot(),(*playerToDelete).getDiffStats()); // add this helper func
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if(playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0){
        return StatusType::INVALID_INPUT;
    }
    player* tmp_player = new player;
    if(!tmp_player){
        delete tmp_player;
        return StatusType::ALLOCATION_ERROR;
    }

    tmp_player = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);
    if(tmp_player == NULL){
        delete tmp_player;
        return StatusType::FAILURE;
    }

    team* tmp_team = m_all_teams.find_by_key(m_all_teams.getRoot(),tmp_player->getMyTeam());
    if(tmp_team == NULL) {
        delete tmp_team;
        return StatusType::FAILURE;
    }

    m_all_players_goals.remove(m_all_players_goals.getRoot(),tmp_player->getMyStats());
    tmp_team->removePlayer(tmp_player->getMyStats(),playerId);

    tmp_player->addCards(cardsReceived);
    tmp_player->addGames(gamesPlayed);
    tmp_player->addGoals(scoredGoals);
    m_all_players_goals.insert(m_all_players_goals.getRoot(),(*tmp_player),tmp_player->getMyStats());
    tmp_team->addPlayer(tmp_player,tmp_player->getMyStats(),playerId);

    delete tmp_player;
    delete tmp_team;

    return StatusType::SUCCESS;
}

//updated
StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }

    team* team1 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId1);
    team* team2 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId2);
    if(!team1 || !team2){
        delete team1;
        delete team2;
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
        team1->updatePoints(3);
        team1->addGamePlayed();
        team2->addGamePlayed();
    }
    else{
        team1->updatePoints(1);
        team2->updatePoints(1);
        team1->addGamePlayed();
        team2->addGamePlayed();
    }
    delete team1;
    delete team2;
    return StatusType::SUCCESS;
}
//updated out
output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    output_t<int> out;
    if(playerId <= 0){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    //todo: maybe put all under try and catch??
    player* player1 = new player*;
    if(!player1){
        delete player1;
        output_t<int> out(StatusType::ALLOCATION_ERROR);
        return out;
    }
    player1 = m_all_players_id.find_by_key(m_all_players_id.getRoot(),playerId);//returns null if haven't found
    if(player1 == NULL){
        delete player1;
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
    output_t<int> out(player1->totalGames());
    delete player1;
	return out;
}
//updated out
output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0){
        output_t<int> out(StatusType::INVALID_INPUT);
 //       out.status() = StatusType::INVALID_INPUT; //fix
        return out;
    }

    //these two might throw exceptions
    team* wanted_team = new team; //fix
    if(!wanted_team){
        output_t<int> out(StatusType::ALLOCATION_ERROR); //fix
        delete wanted_team;
        return out;
    }
    wanted_team = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);//returns NULL if we have not found
    if(wanted_team == NULL){
        output_t<int> out(StatusType::FAILURE); //fix
        delete wanted_team;
        return out;
    }
    delete wanted_team;
    output_t<int> out(wanted_team->getNumPoints());
    return out;
}


//helper merge-sort
void mergeArrays(node<player,playerStats>* arr1[], node<player,playerStats>* arr2[], int m,int n, node<player,playerStats>* arr3[]){
    int i = 0;
    int j = 0;
    int k = 0;

    // Traverse both array
    while (i<m && j <n){
        // Check if current element of first
        // array is smaller than current element
        // of second array. If yes, store first
        // array element and increment first array
        // index. Otherwise do same with second array
        if (arr1[i] < arr2[j])
            arr3[k++] = arr1[i++];
        else
            arr3[k++] = arr2[j++];
    }

    // Store remaining elements of first array
    while (i < m)
        arr3[k++] = arr1[i++];

    // Store remaining elements of second array
    while (j < n)
        arr3[k++] = arr2[j++];
}


StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(newTeamId <= 0 || teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }

    team* team1=m_all_teams.find_by_key(m_all_teams.getRoot(),teamId1);
    team* team2=m_all_teams.find_by_key(m_all_teams.getRoot(),teamId2);

    node<player,playerStats>* arr1[team1->getNumPlayers()];
    node<player,playerStats>* arr2[team2->getNumPlayers()];
    node<player,playerStats>* mergedArr[team2->getNumPlayers()+team1->getNumPlayers()];

    team1->getArray(arr1);
    team2->getArray(arr2);
    mergeArrays(arr1,arr2,team1->getNumPlayers(),team2->getNumPlayers(),mergedArr);

    int height=((int)log2(team2->getNumPlayers()+team1->getNumPlayers()+1))-1;
    AvlTree<player,playerStats> unitedTree=AvlTree<player,playerStats>();
    node<player, playerStats>* root= unitedTree.getRoot();
    unitedTree.createEmptyTree(root,height);
    unitedTree.setRoot(root);
    int toDelete= pow(2,height)-(team2->getNumPlayers()+team1->getNumPlayers());
    unitedTree.makeNearlyEmpty(root, &toDelete);
    unitedTree.arrayToBST(root,mergedArr);

    team newTeam=team(newTeamId,team1->getNumPoints()+team2->getNumPoints());
    newTeam.setTeamTree(unitedTree);
    //todo:
//update team stats, put inside tree, delete old trees
	return StatusType::SUCCESS;
}


//updated out
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
        output_t<int> out(m_top_scorer->getID());
        return out;
    }
    else{
        team* team1 = new team; //fix
        if(!team1){
            output_t<int> out(StatusType::ALLOCATION_ERROR);
            delete team1;
            return out;
        }
        team1 = m_all_teams.find_by_key(teamId);//returns null if the team hasn't found
        if(team1 == NULL){
            output_t<int> out(StatusType::FAILURE);
            delete team1;
            return out;
        }
        output_t<int> out(team1->top_scorer_id());
        delete team1;
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
        team* team1 = new team; //fix
        if(team1 == NULL){
            output_t<int> out(StatusType::ALLOCATION_ERROR);
            delete team1;
            return out;
        }
        team1 = m_all_teams.find_by_key(m_all_teams.getRoot(),teamId);
        if(teamId == NULL){
            output_t<int> out(StatusType::FAILURE);
            delete team1;
            return out;
        }
        output_t<int> out(team1->getNumPlayers());
        delete team1;
        return out;
    }
}
//updated

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if(teamId == 0 || output == NULL){
        return StatusType::INVALID_INPUT;
    }
    if(teamId > 0){
        team* tmp_team = new team;//??
        if(tmp_team == NULL){
            delete tmp_team;
            return StatusType::ALLOCATION_ERROR;
        }
        tmp_team = m_all_teams.find_by_key(teamId);
        if(tmp_team == NULL){
            delete tmp_team;
            return StatusType::FAILURE;
        }
        tmp_team->getTree()->storeInOrderRecursive(tmp_team->getTree()->getRoot(), output); //??
        delete tmp_team;
    }
    else
        m_all_players_different_order.storeInOrderRecursive(m_all_players_different_order.getRoot(), output); //??
    return StatusType::SUCCESS;
}
//updated out
output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if(playerId <= 0 || teamId <= 0){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    team* team1 = m_all_teams.find_by_key(teamId);
    if(team1 == NULL){
        delete team1;
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
    player* player1 = team1->findPlayerById(playerId);
    delete team1;
    if(player1 == NULL){
        delete player1;
        output_t<int> out(StatusType::FAILURE);
        return out;
    }
    output_t<int> out(player1->getClosest()->getId());
    delete player1;
    return out;
}

//todo:
output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId){
        output_t<int> out(StatusType::INVALID_INPUT);
        return out;
    }
    AvlTree<team, int> knockout_tree = m_allowed_to_play_teams;// c'py c'tor
    team* arr_teams = new team[];
    knockout_tree.storeInOrderRecursiveByTerms(minTeamId, maxTeamId, knockout_tree.getRoot(), arr_teams);//probably need to implement in avltree unless there is a better soultion





	// TODO: Your code goes here
	return 2;
}



