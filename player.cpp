//
// Created by 97254 on 21/11/2022.
//

#include "player.h"
#include "team.h"


player::player(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper)
{
    m_playerId=playerId;
    m_cards=cards;
    m_gamesPlayed=gamesPlayed;
    m_goals=goals;
    m_goalKeeper=goalKeeper;
    m_teamGamesWO= playerTeam.getNumGames;
}

int totalGames(team* playerTeam)
{
    int teamGames = playerTeam->getNumGames();
    return teamGames+m_gamesPlayed-m_teamGamesWO;
}