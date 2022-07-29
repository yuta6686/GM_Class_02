#pragma once
#include "ComponentObject.h"
class Enemy_Interface :
    public ComponentObject
{
private:    
    int m_MaxHp=1;
    int m_Hp = m_MaxHp;
    static const int MAX_HP = 9999;
public:
    int GetMaxHp() { return m_MaxHp; }
    int GetHp() { return m_Hp; }    
    virtual bool SetHp(const int& hp) {
        if (hp < 0 || hp >= MAX_HP) {
            m_Hp = 1;
            return false;
        }
        m_Hp = hp;
        return true;
    }

    virtual bool SetMaxHp(const int& hp) 
    {
        if (hp < 0 || hp >= MAX_HP) {
            m_MaxHp = 1;
            return false;
        }
        m_MaxHp = hp;
        return true;
    }
    void CollosionWithBullet()
    {
        m_Hp--;

        if (m_Hp <= 0) {
            SetDestroy();
        }
    }

    void CollosionWithBullet(int damage)
    {
        m_Hp -= damage;

        if (m_Hp <= 0) {
            SetDestroy();
        }
    }
};

