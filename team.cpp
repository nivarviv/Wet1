
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
    m_top_scorer = NULL; ///to do
    m_tree_by_id = AvlTree<player, int>();
    m_tree_by_stats = AvlTree<player, playerStats>();
    m_numGoalKeepers=0;
    m_tree_by_diff_stats=AvlTree<player, playerStatsDifferentOrder>();
}

int team::getNumGames(){
    return m_num_games;
}

int team::getNumPoints(){
    return m_points;
}

int team::top_scorer_id() const{
    return m_top_scorer->getId();
}

int team::getNumPlayers()
{
    return m_num_players;
}

void team::getArrayStats(node<player,playerStats>** arr1)
{
    node<player,playerStats>* root=m_tree_by_stats.getRoot();
    m_tree_by_stats.storeInOrderRecursive(root,arr1);
}

void team::setTeamTree(AvlTree<player, playerStats> tree) {
    m_tree_by_stats=tree;
}

player* team::findPlayerById(int id) {
    return m_tree_by_id.find_by_key(m_tree_by_id.getRoot(),id);
}

void team::addPlayer(player* player, playerStats stats,int id) {
    m_tree_by_stats.insert(m_tree_by_stats.getRoot(),(*player),stats);
    m_tree_by_id.insert(m_tree_by_id.getRoot(),(*player),id);
    m_num_players++;
    if((*player).isGoalKeeper()){
        m_has_goalkeeper=true;
    }
}

bool team::isTeamValid() const {
    if(m_has_goalkeeper && m_num_players >= 11){
        return true;
    }
    return false;
}

void team::removePlayer(playerStats stats, int id) {
    m_tree_by_stats.remove(m_tree_by_stats.getRoot(),stats);
    m_tree_by_id.remove(m_tree_by_id.getRoot(),id);
    m_num_players--;
    if((*player).isGoalKeeper()){
        m_numGoalKeepers--;
        if(m_numGoalKeepers==0){
            m_has_goalkeeper= false;
        }
    }
}

team::~team() {
    delete m_top_scorer;
}

/*const AvlTree<player, int>* team::getTreeId() const {!!
    return &m_tree_by_id;
}*/

int team::getNumGoals() {
    return m_total_goals;
}

int team::getNumCards() {
    return m_total_cards;
}

void team::updatePoints(int pointsToAdd) {
    m_points+=pointsToAdd;
}

void team::addGamePlayed() {
    m_num_games++;
}

/*AvlTree<player, playerStats>* team::getTreeStats() const{
    return m_tree_by_stats;
}
AvlTree<player, playerStatsDifferentOrder>* team::getTreeDiffStats() const{
    return m_tree_for_all_players;
}*/

int team::getId() const {
    return m_teamId;
}

void team::getArrayDiffStats(int const *arr1) {
    node<player,playerStatsDifferentOrder>* root=m_tree_by_diff_stats.getRoot();
    m_tree_by_diff_stats.storeInOrderRecursiveKey(root,arr1);
}
