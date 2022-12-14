
//
// Created by 97254 on 21/11/2022.!
//

#include "team.h"
#include "player.h"
team::team(int teamId, int points) : m_num_players(0), m_has_goalkeeper(false), m_total_goals(0), m_total_cards(0), m_points(points), m_num_games(0), m_teamId(teamId), m_top_scorer(
        nullptr), m_tree_by_id(AvlTree<player, int>()), m_tree_by_stats(AvlTree<player, playerStats>()), m_numGoalKeepers(0)
{
   /* m_num_players=0;
    m_has_goalkeeper=false;
    m_total_goals=0;
    m_total_cards=0;
    m_total_cards=0;
    m_points=points;
    m_num_games=0;
    m_teamId=teamId;
    m_top_scorer = nullptr; ///to do
    m_tree_by_id = AvlTree<player, int>();
    m_tree_by_stats = AvlTree<player, playerStats>();
    m_numGoalKeepers=0;*/
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

/*void team::getArrayStats(node<player,playerStats>** arr1)
{
    node<player,playerStats>* root=m_tree_by_stats.getRoot();
    m_tree_by_stats.storeInOrderRecursive(root,arr1);
}*/

void team::setTeamTree(AvlTree<player, playerStats> treeStats,AvlTree<player, int> treeID) {
    m_tree_by_stats=treeStats;
    m_tree_by_id=treeID;
}

std::shared_ptr<player> team::findPlayerById(int id) {
    return m_tree_by_id.find_by_key(m_tree_by_id.getRoot(),id);
}

void team::addPlayer(std::shared_ptr<player> player, playerStats stats,int id) {
    m_tree_by_id.insert(m_tree_by_id.getRoot(),player,id);
    m_tree_by_stats.insert(m_tree_by_stats.getRoot(),player,stats);
    m_num_players++;
    if((*player).isGoalKeeper()){
        m_has_goalkeeper=true;
    }
    m_total_goals += player->getGoals();
    m_total_cards += player->getCards();
}

bool team::isTeamValid() const {
    if(m_has_goalkeeper && m_num_players >= 11){
        return true;
    }
    return false;
}

team::~team() {

    //delete m_top_scorer;
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

void team::getArrayId(int *const arr1) {
    node<player,playerStats>* root=m_tree_by_stats.getRoot();
    int index=0;
    m_tree_by_stats.storeInOrderRecursiveKey(m_tree_by_stats.getRoot(),&index,arr1);
}

void team::deleteTeam() {
    m_tree_by_stats.deleteTree(m_tree_by_stats.getRoot());
    m_tree_by_id.deleteTree(m_tree_by_id.getRoot());
    m_num_players=0;
}

playerStats team::getTopScorerStats() const{
    if(m_top_scorer == nullptr){
        playerStats tmp(0, INT8_MAX, 0);
        return tmp;
    }
    return m_top_scorer->getMyStats();
}

void team::setTopScorer(std::shared_ptr<player> player){
    m_top_scorer = player;
}
void team::removePlayer(playerStats stats, int id) {
    std::shared_ptr<player> tmp = m_tree_by_id.find_by_key(m_tree_by_id.getRoot(), id);
    if(tmp == nullptr){
        return;
    }
    if(tmp->isGoalKeeper()){
        m_numGoalKeepers--;
        if(m_numGoalKeepers == 0){
            m_has_goalkeeper = false;
        }
    }
    m_tree_by_stats.remove(m_tree_by_stats.getRoot(),stats);
    m_tree_by_id.remove(m_tree_by_id.getRoot(),id);
    m_num_players--;
}


std::shared_ptr<player> team::getTopScorer() const{
    return m_top_scorer;
}


std::shared_ptr<player> team::getTopNewScorer(){
    return m_tree_by_stats.getBiggest(m_tree_by_stats.getRoot());
}

void team::storeTree(std::shared_ptr<player>*arrT1, playerStats **arrK1){
    int i = 0;
    m_tree_by_stats.storeInorder(m_tree_by_stats.getRoot(), arrT1, arrK1, &i);
}

void team::storeTreeSingle(std::shared_ptr<player> *arrT1) {
    int i = 0;
    m_tree_by_stats.storeInorderSingle(m_tree_by_stats.getRoot(), arrT1, &i);
}

void team::storeTreeSingleInt(int** array) {
    int i = 0;
    m_tree_by_id.storeInorderSingleInt(m_tree_by_id.getRoot(), array, &i);
}

AvlTree<player, int> team::getIdTree() const {
    return m_tree_by_id;
}
/*

AvlTree<player, playerStats> *team::getTreeStats() {
    return &m_tree_by_stats;
}
*/
