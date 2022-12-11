//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H
#include "playerStats.h"
#include <iostream>
#include <memory>

class team;


class player {
private:
    int m_playerId;
    std::shared_ptr<team> m_my_team;
    int m_teamId;
    int m_gamesPlayed;//before joining
    playerStats m_stats{};
    int m_goals;
    int m_cards;
    bool m_goalKeeper;
    std::shared_ptr<player> m_closest;
    std::shared_ptr<player> m_pre;
    std::shared_ptr<player> m_suc;
    int m_teamGamesWO; // num games the team played without him!!

public:
    player();
    player(int playerId,int teamId,std::shared_ptr<team> playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper);
    player addNewPlayer(int playerId,std::shared_ptr<team> playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper);
    player(const player& other);
    ~player();
    player& operator=(const player& other);
    bool operator==(const player &p) const;
    int totalGames() const;
    std::shared_ptr<team> getMyTeam() const;
    playerStats getMyStats() const;
    std::shared_ptr<player> closestOfTwoExist(std::shared_ptr<player> pre, std::shared_ptr<player> suc) const;
    std::shared_ptr<player> closestOfTwo(std::shared_ptr<player> pre, std::shared_ptr<player> suc) const;
    void setClosest(std::shared_ptr<player> player);
    void setPre(std::shared_ptr<player> player);
    void setSuc(std::shared_ptr<player> player);
    std::shared_ptr<player> getPre() const;
    std::shared_ptr<player> getSuc() const;
    std::shared_ptr<player> getClosest() ;
    bool isGoalKeeper() const;
    void addGoals(int goals);
    void addGames(int games_played);
    void addCards(int cards);
    int getId() const;
    void setMyTeam(std::shared_ptr<team> new_team);
    int getTeamId();
    void updateStats();
    int getGoals() const;
    int getCards() const;
};



#endif //WET1_PLAYER_H
