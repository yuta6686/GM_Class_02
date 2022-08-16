#pragma once
#include "Component.h"
#include "gameObject.h"
#include "UserInterfaceComponent.h"
class HPComponent :
    public Component
{
private:
    int m_Hp = 10;    
    int m_MaxHp = 10;    
    bool m_IsDeath = false;
    UserInterfaceComponent* m_UIComponent = nullptr;
    inline static const float MERGINE = 50.0f;
    inline static const float LEFT_POSITION = MERGINE;
    inline static const float RIGHT_POSITION = 500.0f - MERGINE;
public:
    static float GetLEFTPOSITION() { return LEFT_POSITION; }
    static float GetRIGHTPOSITION() { return RIGHT_POSITION; }
    bool GetIsDeath()const { return m_IsDeath; }

    void RecoverHp(const int& hp) 
    {
        m_Hp += hp;
        if (m_Hp > m_MaxHp)
        {
            m_Hp = m_MaxHp;
        }
    }
    void ResetHp() 
    {
        m_Hp = m_MaxHp;
    }
    void SetMaxHp(const int& maxHp) 
    {
        m_MaxHp = maxHp;
    }
    void TakeDamage(const int& damage)
    {
        m_Hp -= damage;

        if (m_Hp <= 0) {
            m_IsDeath = true;
        }
    }
    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

