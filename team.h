//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H


class team {
private:
    int m_num_players;
    bool m_has_goalkeeper;
    int m_total_goals;
    int m_total_cards;
    int m_points;
    int m_num_games;
    int m_teamId
    //player* top_scorer;

    //

public:
    team(int teamId, int points);
    int getNumGames();
    player(const player&) = default;
    ~player() = default;
    player& operator=(const player& other) = default;

};


#endif //WET1_TEAM_H
