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
    team* m_my_team;
    int m_gamesPlayed;//before joining
    playerStats m_stats;
    int m_goals;
    int m_cards;
    bool m_goalKeeper;
    playerStats m_stats;
    player* m_closest;
    player* m_pre;
    player* m_suc;
    int m_teamGamesWO; // num games the team played without him

public:
    player(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper);
    player addNewPlayer(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper);
    //player(const player&) = default;// I think we need to do it not by default due to there is memory allocation
    ~player();
    player& operator=(const player& other) = default;
    int totalGames() const;
    team* getMyTeam() const;
    playerStats getMyStats() const;
    player* closestOfTwo(player* pre, player* suc);
    void setClosest(player* player);
    void setPre(player* player);
    void setSuc(player* player);
    player* getPre();
    player* getSuc();
    player* getClosest();
    bool isGoalKeeper();
    void addGoals(int goals);
    void addGames(int games_played);
    void addCards(int cards);
};



#endif //WET1_PLAYER_H
