//
// Created by 97254 on 25/11/2022.
//

#include "playerStats.h"
bool playerStats::operator<(const playerStats& ps) const{
    if(this->m_goals < ps.m_goals){
        return true;
    }
    else if(this->m_goals < ps.m_goals){
        return false;
    }
    else{
       if(this->m_cards < ps.m_cards){
           return true;
       }
       else if(this->m_cards > ps.m_goals){
           return false;
       }
       else{
           if(this->m_id < ps.m_id){
               return true;
           }
           else if(this->m_id > ps.m_id){
               return false;
           }
       }
    }
}
bool playerStats::operator>(const playerStats& ps) const{
    return (ps < *this);//this or *this?
}