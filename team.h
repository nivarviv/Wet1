//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "AvlTree.h"
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
    int m_teamId
    player* m_top_scorer;
    AvlTree<player, int> m_tree_by_id;
    AvlTree<player, playerStats> m_tree_by_stats;

    //

public:
    team(int teamId, int points);
    int getNumGames();
    team(const team&) = default;//we don't want to allow that
    ~team() = default;
    team& operator=(const team& other) = default;//we don't want to allow that
    void add_player(int player_id, int games_played, int goals, int cards, bool goalkeeper);
    int top_scorer_id() const;
};


#endif //WET1_TEAM_H
