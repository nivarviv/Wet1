#include "worldcup23a1.h"
//updated
world_cup_t::world_cup_t()
{
    m_all_teams = AvlTree<team, int>();
    m_allowed_to_play_teams = AvlTree<team, int>();
    m_all_players_id = AvlTree<player, int>();
    m_all_players_goals = AvlTree<player, playerStats>();
    m_top_scorer = NULL;
    m_total_players = 0;
}
//updated
world_cup_t::~world_cup_t()
{
    delete m_all_teams;
    delete m_allowed_to_play_teams;
    delete m_total_players;
    delete m_all_players_goals;
    delete m_all_players_id;
    delete m_top_scorer;
}
//updated
StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId <= 0 || points < 0){
        return StatusType::INVALID_INPUT;
    }
    team* tmp = m_all_teams.find_by_key(teamId);
    if(tmp == NULL){//it returns null if we haven't found such team
        delete tmp;
        return StatusType::FAILURE;
    }
    team team1 = team(teamId, points);
    //check for exception
    m_all_teams.add(team1, teamId);
    delete tmp;
	return StatusType::SUCCESS;
}
//updated
StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    team* team1 = m_all_teams.find_by_key(teamId);
    if(!team1){
        delete team1;
        return StatusType::FAILURE;
    }
    if(team1->m_num_players){
        delete team1;
        return StatusType::FAILURE;
    }
    else{
        m_all_teams.remove_by_key(teamId);
        delete team1;
        return StatusType::SUCCESS;
    }
}
//todo:
StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if(playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 ||
        cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0))){
        return StatusType::INVALID_INPUT;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
//todo:
StatusType world_cup_t::remove_player(int playerId)
{
    if(playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
//todo:
StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if(playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0){
        return StatusType::INVALID_INPUT;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
//updated
StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    team* team1 = new team;
    team* team2 = new team;
    if(!team1||!team2){
        delete team1;
        delete team2;
        return StatusType::ALLOCATION_ERROR;
    }
    team1 = m_all_teams.find_by_key(teamId1);
    team2 = m_all_teams.find_by_key(teamId2);
    if(!team1 || !team2){
        delete team1;
        delete team2;
        return StatusType::FAILURE;
    }
    int sum1 = team1->m_points + team1->m_goals - team1->m_cards;
    int sum2 = team2->m_points + team2->m_goals - team2->m_cards;
    if(sum1 > sum2){
        team1->m_points += 3;
        team1->m_num_games++;
        team2->m_num_games++;
    }
    else if(sum2>sum1){
        team1->m_points += 3;
        team1->m_num_games++;
        team2->m_num_games++;
    }
    else{
        team1->m_points++;
        team2->m_points++;
        team1->m_num_games++;
        team2->m_num_games++;
    }
    delete team1;
    delete team2;
    return StatusType::SUCCESS;
}
//updated
output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    output_t<int> out;
    if(playerId <= 0){
        out.status() = StatusType::INVALID_INPUT;
        return out;
    }
    player* player1 = new player*;
    if(!player1){
        delete player1;
        out.status() = StatusType::ALLOCATION_ERROR;
        return out;
    }
    player1 = all_players_id.find_by_key(playerId);//returns null if haven't found
    if(player1 == NULL){
        delete player1;
        out.status() = StatusType::FAILURE;
        return out;
    }
    out.ans() = player1->m_gamesPlayed;
    out.status() = StatusType::SUCCESS;
    delete player1;
	return out;
}
//updated
output_t<int> world_cup_t::get_team_points(int teamId)
{
    output_t<int> out;
    if(teamId <= 0){
        out.status() = StatusType::INVALID_INPUT;
        return out;
    }

    //these two might throw exceptions
    team* wanted_team = new team;
    if(!wanted_team){
        out.status() = StatusType::ALLOCATION_ERROR;
        delete wanted_team;
        return out;
    }
    wanted_team = m_all_teams.find_by_key(teamId);//returns NULL if we have not found
    if(wanted_team == NULL){
        out.status() = StatusType::FAILURE;
        delete wanted_team;
        return out;
    }
    out.ans() = wanted_team->m_points;
    out.status() = StatusType::SUCCESS;
    delete wanted_team;
    return out;
}
//todo:
StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(newTeamId <= 0 || teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
//updated
output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    output_t<int> out;
    if(teamId == 0){
        out.status() = StatusType::INVALID_INPUT;
        return out;
    }
    else if(teamId < 0){
        if(total_players <= 0){
            out.status() = StatusType::FAILURE;
            return out;
        }
        out.ans() = m_top_scorer->m_playerId;
        out.status() = StatusType::SUCCESS;
        return out;
    }
    else{
        team* team1 = new team*;
        if(!team1){
            out.status() = StatusType::ALLOCATION_ERROR;
            delete team1;
            return out;
        }
        team1 = m_all_teams.find_by_key(teamId);//returns null if the team hasn't found
        if(team1 == NULL){
            out.status() = StatusType::FAILURE;
            delete team1;
            return out;
        }
        out.ans() = team1->top_scorer_id();
        out.status() = StatusType::SUCCESS;
        delete team1;
        return out;
    }
}
//updated
output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    output_t<int> out;
    if(teamId == 0){
        out.status() = StatusType::INVALID_INPUT;
        return out;
    }
    else if (teamId < 0){
        out.ans() = total_players;
        out.status() = StatusType::SUCCESS;
        return out;
    }
    else{
        team* team1 = new team*;
        if(team1 == NULL){
            out.status() = StatusType::ALLOCATION_ERROR;
            delete team1;
            return out;
        }
        team1 = m_all_teams.find_by_key(teamId);
        if(teamId == NULL){
            out.status() = StatusType::FAILURE;
            delete team1;
            return out;
        }
        out.ans() = team1->num_players;
        out.status() = StatusType::SUCCESS;
        delete team1;
        return out;
    }
}
//todo:
StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if(teamId == 0 || output == NULL){
        return StatusType::INVALID_INPUT;
    }
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}
//todo:
output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if(playerId <= 0 || teamId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
	// TODO: Your code goes here
	return 1006;
}
//todo:
output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
	// TODO: Your code goes here
	return 2;
}

