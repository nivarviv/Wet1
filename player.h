//
// Created by 97254 on 21/11/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H


class player {
private:
    int m_playerId;
    int m_cards;
    int m_gamesPlayed;//before joining
    //int totalGames;
    int m_goals;
    bool m_goalKeeper;
    int m_teamGamesWO; // num games the team played without him
    //pointer to my team
    //num_games+gamesplayed-without
public:
    player(int playerId, team* playerTeam, int gamesPlayed, int goals, int cards, bool goalKeeper);
    player(const player&) = default;
    ~player() = default;
    player& operator=(const player& other) = default;
    int totalGames(int playerGames, int teamGames, int gamesWithout);
};



#endif //WET1_PLAYER_H
