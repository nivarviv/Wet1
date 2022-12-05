//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "player.h"
#include "playerStats.h"
#include "AvlTree.h"

class team {
private:
    int m_num_players;
    bool m_has_goalkeeper;
    int m_total_goals;
    int m_total_cards;
    int m_points;
    int m_num_games;
    int m_teamId
    player* m_top_scorer;
    AvlTree<player, int> m_tree_by_id;
    AvlTree<player, playerStats> m_tree_by_stats;
    int m_numGoalKeepers;
    AvlTree<player, playerStatsDifferentOrder> m_tree_for_all_players;

    //

public:
    team(int teamId, int points);
    int getNumGames();
    team(const team&) = default;//we don't want to allow that
    ~team();
    team& operator=(const team& other) = default;//we don't want to allow that
    void addPlayer(player* player, playerStats stats,int id);
    void removePlayer(playerStats stats, int id);
    int top_scorer_id() const;
    int getNumPlayers();
    int getNumPoints();
    void setTeamTree( AvlTree<player, playerStats> tree);
    void getArray(node<player,playerStats>** arr1);
    player* findPlayerById(int id);
    bool isTeamValid() const;
    const AvlTree<player, int> getTree() const;
    const AvlTree<player, playerStats> getTree() const;
    const AvlTree<player, playerStatsDifferentOrder> getTree() const;
    int getNumGoals();
    int getNumCards();
    void updatePoints(int pointsToAdd);
    void addGamePlayed();
};


#endif //WET1_TEAM_H
