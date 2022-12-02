//
// Created by 97254 on 21/11/2022.
//

#include "player.h"


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
