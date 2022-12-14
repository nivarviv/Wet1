//
// Created by 97254 on 21/11/2022.
//!
#include "AvlTree.h"
#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "player.h"
#include "playerStats.h"


class team {
private:
    int m_num_players;
    bool m_has_goalkeeper;
    int m_total_goals;
    int m_total_cards;
    int m_points;
    int m_num_games;
    int m_teamId;
    std::shared_ptr<player> m_top_scorer;
    AvlTree<player, int> m_tree_by_id;
    AvlTree<player, playerStats> m_tree_by_stats;
    int m_numGoalKeepers;

    //

public:
    team(int teamId, int points);
    int getNumGames();
    team(const team&) = default;//we don't want to allow that!!
    ~team();
    team& operator=(const team& other) = default;//we don't want to allow that
    void addPlayer(std::shared_ptr<player> player, playerStats stats,int id);
    void removePlayer(playerStats stats, int id);
    // void addPlayer(player* player, playerStats stats,int id);
    int top_scorer_id() const;
    int getNumPlayers();
    int getNumPoints();
    void setTeamTree( AvlTree<player, playerStats> treeStats,AvlTree<player, int> treeID);
    AvlTree<player, int> getIdTree() const;
    //void getArrayStats(node<player,playerStats>** arr1);
    std::shared_ptr<player> findPlayerById(int id);
    bool isTeamValid() const;
    int getNumGoals();
    int getNumCards();
    void updatePoints(int pointsToAdd);
    void addGamePlayed();
    int getId() const;
    void deleteTeam();
    playerStats getTopScorerStats() const;
    std::shared_ptr<player> getTopScorer() const;
    void setTopScorer(std::shared_ptr<player> player);
    std::shared_ptr<player> getTopNewScorer();
    void getArrayId(int *const arr1);

    /* AvlTree<player, int>* getTreeId() const;
    AvlTree<player, playerStats>* getTreeStats() const;*/

    void storeTree(std::shared_ptr<player> *arrT1, playerStats **arrK1);
    void storeTreeSingle(std::shared_ptr<player> *arrT1);
    void storeTreeSingleInt(int** array);
};


#endif //WET1_TEAM_H
