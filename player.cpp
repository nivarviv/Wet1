//
// Created by 97254 on 21/11/2022.
//

#include "player.h"
#include <math.h>


player::player(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper){
    m_playerId = playerId;
    m_my_team = playerTeam;
    m_gamesPlayed = gamesPlayed;
    m_goals = goals;
    m_cards = cards;
    m_goalKeeper = goalKeeper;
    m_stats = playerStats(playerId, cards, goals);
    //m_closest=?
    m_teamGamesWO = playerTeam->getNumGames();
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

player *player::closestOfTwo(player *pre, player *suc) {
    if(abs(this->m_goals-pre->m_goals)<abs(this->m_goals-suc->m_goals))
        return pre;
    else if(abs(this->m_goals-pre->m_goals)>abs(this->m_goals-suc->m_goals))
        return suc;
    else if(abs(this->m_cards-pre->m_cards)<abs(this->m_cards-suc->m_cards))
        return pre;
    else if(abs(this->m_cards-pre->m_cards)>abs(this->m_cards-suc->m_cards))
        return suc;
    else
        return (pre->m_playerId > suc->m_playerId) ? pre : suc;
}
