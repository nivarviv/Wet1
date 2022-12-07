//
// Created by 97254 on 01/12/2022.
//

#include "playerStatsDifferentOrder.h"


bool playerStatsDifferentOrder::operator<(const playerStatsDifferentOrder& ps) const{
    if(this->m_goals < ps.m_goals){
        return true;
    }
    else if(this->m_goals > ps.m_goals){
        return false;
    }
    else{
        if(this->m_cards > ps.m_cards){
            return true;
        }
        else if(this->m_cards < ps.m_goals){
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
    return false;
}
bool playerStatsDifferentOrder::operator>(const playerStatsDifferentOrder& ps) const{
    return (ps < *this);//this or *this?
}