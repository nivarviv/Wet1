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
    playerStats m_stats;
    int m_goals;
    bool m_goalKeeper;
    int m_teamGamesWO; // num games the team played without him
    player* m_closest;
    player* m_pre;
    player* m_suc;
    team* m_my_team;

public:
    player(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper);
    player(const player&) = default;// I think we need to do it not by default due to there is memory allocation
    ~player() = default;
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


};



#endif //WET1_PLAYER_H
