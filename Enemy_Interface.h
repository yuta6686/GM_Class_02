#pragma once
#include "gameObject.h"
class Enemy_Interface :
    public GameObject
{
private:    
    int m_MaxHp=1;
    int m_Hp = m_MaxHp;
public:
    virtual void Init() override=0;
    virtual void Uninit() override=0;
    virtual void Update() override=0;
    virtual void Draw() override=0;

    virtual bool SetMaxHp(const int& hp) 
    {
        if (hp < 0 || hp >= 9999) {
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
