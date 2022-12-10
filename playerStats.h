//
// Created by 97254 on 25/11/2022.
//

#ifndef WORLDCUP23A1_H_PLAYERSTATS_H
#define WORLDCUP23A1_H_PLAYERSTATS_H

class playerStats {
private:
    int m_id;
    int m_cards;
    int m_goals;
public:
    playerStats() = default;
    playerStats(int id, int cards, int goals): m_id(id), m_cards(cards), m_goals(goals){}
    ~playerStats() = default;
    playerStats(const playerStats& other) = default;
    playerStats& operator=(const playerStats& other)= default;
    bool operator<(const playerStats& ps) const;
    bool operator>(const playerStats& ps) const;
    bool operator==(const playerStats& ps) const;
};


#endif //WORLDCUP23A1_H_PLAYERSTATS_H
