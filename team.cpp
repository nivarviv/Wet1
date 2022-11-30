
//
// Created by 97254 on 21/11/2022.
//

#include "team.h"

team::team(int teamId, int points)
{
    m_num_players=0;
    m_has_goalkeeper=false;
    m_total_goals=0;
    m_total_cards=0;
    m_points=points;
    m_num_games=0;
    m_teamId=teamId;
    m_top_scorer = NULL;
    m_tree_by_id = AvlTree<player, int>(); //check if needed
    m_tree_by_stats = AvlTree<player, playerStats>();
}

int team::getNumGames(){
    return m_num_games;
}


int team::top_scorer_id() const{
    return m_top_scorer->m_playerId;
}

int team::getNumPlayers()
{
    return m_num_players;
}

void team::getArray(player** arr1)
{
    m_tree_by_stats.storeInOrderRecursive(arr1);
}


