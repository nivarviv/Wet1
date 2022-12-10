//
// Created by 97254 on 21/11/2022.
//

#include "player.h"
#include "team.h"



player::player(int playerId,int teamId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper) :
        m_playerId(playerId),m_teamId(teamId) ,m_my_team(playerTeam), m_gamesPlayed(gamesPlayed), m_goals(goals), m_cards(cards), m_goalKeeper(goalKeeper),
        m_stats(playerStats(playerId, cards, goals)), m_closest(nullptr), m_pre(nullptr), m_suc(nullptr), m_teamGamesWO(0)
{
    m_teamGamesWO = (*m_my_team).getNumGames();
}

int player::totalGames() const{
    return m_gamesPlayed + m_my_team->getNumGames() - m_teamGamesWO;
}

playerStats player::getMyStats() const{
    return m_stats;
}

team* player::getMyTeam() const{
    return m_my_team;
}

void player::setClosest(player* player) {
    m_closest=player;
}



player* player::closestOfTwo(player* pre, player* suc) const{
    if(pre == nullptr && suc == nullptr){
        return nullptr;
    }
    else if(pre == nullptr && suc != nullptr){
        return suc;
    }
    else if(pre != nullptr && suc == nullptr){
        return pre;
    }
    else{
        return closestOfTwoExist(pre, suc);
    }
}


//need to check according to the new instructions
player* player::closestOfTwoExist(player *pre, player *suc) const{
    if(abs(this->m_goals-pre->m_goals)<abs(this->m_goals-suc->m_goals)){
        return pre;
    }
    else if(abs(this->m_goals-pre->m_goals)>abs(this->m_goals-suc->m_goals)){
        return suc;
    }
    else if(abs(this->m_cards-pre->m_cards)<abs(this->m_cards-suc->m_cards)){
        return pre;
    }
    else if(abs(this->m_cards-pre->m_cards)>abs(this->m_cards-suc->m_cards)){
        return suc;
    }
    else{
        return (pre->m_playerId > suc->m_playerId) ? pre : suc;
    }
}

void player::setPre(player *player) {
    m_pre=player;
}

void player::setSuc(player *player) {
    m_suc=player;
}

player *player::getPre() const{
    return m_pre;
}

player *player::getSuc() const{
    return m_suc;
}

player* player::getClosest() const{
    return m_closest;
}

player player::addNewPlayer(int playerId, team *playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper) {
    player newPlayer = player(playerId,playerTeam->getId(), playerTeam, gamesPlayed, goals, cards, goalKeeper);
    return newPlayer;
}

bool player::isGoalKeeper() const{
    return m_goalKeeper;
}

void player::addGoals(int goals){
    m_goals += goals;
}

void player::addCards(int cards) {
    m_cards += cards;
}

void player::addGames(int games_played) {
    m_gamesPlayed += games_played;
}

player::~player() {
    delete m_closest;
    delete m_pre;
    delete m_suc;
    delete m_my_team;
}


int player::getId() const{
    return m_playerId;
}

void player::setMyTeam(team* new_team){
    m_my_team = new_team;
}

int player::getTeamId() {
    return m_teamId;
}

player::player() : m_playerId(0),m_teamId(0) ,m_my_team(nullptr), m_gamesPlayed(0), m_goals(0), m_cards(0), m_goalKeeper(false),
                   m_stats(playerStats(0, 0, 0)), m_closest(nullptr), m_pre(nullptr), m_suc(nullptr), m_teamGamesWO(0){}

player &player::operator=(const player &other) {
    if (this==&other){
        return *this;
    }
    m_playerId=other.m_playerId;
    m_my_team=other.m_my_team;
    m_teamId=other.m_teamId;
    m_gamesPlayed=other.m_gamesPlayed;
    m_stats=other.m_stats;
    m_goals=other.m_goals;
    m_cards=other.m_cards;
    m_goalKeeper=other.m_goalKeeper;
    m_closest=other.m_closest;
    m_pre=other.m_pre;
    m_suc=other.m_suc;
    m_teamGamesWO=other.m_teamGamesWO;
    return *this;
}

void player::updateStats() {
m_stats=playerStats(m_playerId, m_cards, m_goals);
}

bool player::operator==(const player &p) const {
    if(m_playerId == p.m_playerId){
        return true;
    }
    return false;
}

player::player(const player &other) {
    m_playerId=other.m_playerId;
    m_my_team=other.m_my_team;
    m_teamId=other.m_teamId;
    m_gamesPlayed=other.m_gamesPlayed;
    m_stats=playerStats(other.m_playerId, other.m_cards, other.m_goals);
    m_goals=other.m_goals;
    m_cards=other.m_cards;
    m_goalKeeper=other.m_goalKeeper;
    m_closest=other.m_closest;
    m_pre=other.m_pre;
    m_suc=other.m_suc;
    m_teamGamesWO=other.m_teamGamesWO;
}
