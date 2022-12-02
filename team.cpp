
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

int team::getNumPoints(){
    return m_points;
}

int team::top_scorer_id() const{
    return m_top_scorer->m_playerId;
}

int team::getNumPlayers()
{
    return m_num_players;
}

void team::getArray(node<player,playerStats>** arr1)
{
    node<player,playerStats>* root=m_tree_by_stats.getRoot();
    m_tree_by_stats.storeInOrderRecursive(root,arr1);
}

void team::setTeamTree(AvlTree<player, playerStats> tree) {
    m_tree_by_stats=tree;
}

player* team::findPlayerById(int id) {
    return m_tree_by_id.find_by_key(id);
}


