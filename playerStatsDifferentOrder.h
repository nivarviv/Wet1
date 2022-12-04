//
// Created by 97254 on 01/12/2022.
//

#ifndef HEAD_PLAYERSTATSDIFFERENTORDER_H
#define HEAD_PLAYERSTATSDIFFERENTORDER_H
//and it's probably code duplicate as well, but for now that's what I have managed to think of so far.
//I'll probably need to think of another name for that class as well:|
//but the purpose of this class is to get stats sort in a different way for get_all_players function
class playerStatsDifferentOrder {
private:
    int m_id;
    int m_cards;
    int m_goals;
public:
    playerStatsDifferentOrder() = default;
    playerStatsDifferentOrder(int id, int cards, int goals): m_id(id), m_cards(cards), m_goals(goals){}
    ~playerStatsDifferentOrder() = default;
    bool operator<(const playerStatsDifferentOrder& ps) const;
    bool operator>(const playerStatsDifferentOrder& ps) const;
};


#endif //HEAD_PLAYERSTATSDIFFERENTORDER_H
