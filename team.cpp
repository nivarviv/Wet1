<<<<<<< HEAD
//
// Created by 97254 on 21/11/2022.
//

#include "team.h"

team::team(int teamId, int points)
{
    m_num_players=0;
    m_has_goalkeeper=false;
    m_total_goals=0;
    m_total_cards=0;
    m_points=points;
    m_num_games=0;
    m_teamId=teamId;
}

int getNumGames(){
    return m_num_games;
}
===