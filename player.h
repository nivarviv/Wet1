//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H
#include "playerStats.h"
#include "team.h"

class player {
private:
    int m_playerId;
    int m_cards;
    int m_gamesPlayed;//before joining
    //int totalGames;
    playerStats m_stats;
    int m_goals;
    bool m_goalKeeper;
    int m_teamGamesWO; // num games the team played without him
    player* m_closest;
    team* m_my_team;
    //num_games+gamesplayed-without
public:
    player(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper);
    player(const player&) = default;
    ~player() = default;
    player& operator=(const player& other) = default;
    int totalGames(team* playerTeam);
};



#endif //WET1_PLAYER_H
