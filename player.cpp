//
// Created by 97254 on 21/11/2022.
//

#include "player.h"
#include <math.h>


player::player(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper) :
                m_playerId(playerId), m_my_team(playerTeam), m_gamesPlayed(gamesPlayed), m_goals(goals), m_cards(cards), m_goalKeeper(goalKeeper),
                m_stats(playerStats(playerId, cards, goals)), m_closest(NULL), m_pre(NULL), m_suc(NULL), m_teamGamesWO(0)
                {
    m_teamGamesWO = (*m_my_team).getNumGames();
                }

int player::totalGames() const{
    return m_gamesPlayed + (*m_my_team).getNumGames() - m_teamGamesWO;
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
//need to check according to the new instructions
player *player::closestOfTwo(player *pre, player *suc) const{
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

player *player::getClosest() const{
    return m_closest;
}

player player::addNewPlayer(int playerId, team *playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper) {
    player newPlayer=player(playerId, playerTeam, gamesPlayed, goals, cards, goalKeeper);
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

