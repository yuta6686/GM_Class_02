#pragma once
#include "ComponentObject.h"
#include "TrackingComponent.h"
#include "StageLimitComponent.h"

#include "ParticleObject.h"
enum ENEMY
{
    ENEMY_NORMAL,
    ENEMY_TRACKING,
    ENEMY_TRACKING_FAST,
    ENEMY_TRACKING_LATE,
    ENEMY_MAX
};
class Enemy_Interface :
    public ComponentObject
{
protected:    
    int m_MaxHp=1;
    int m_Hp = m_MaxHp;
    static const int MAX_HP = 9999;
    int m_EnemyIndex = ENEMY_NORMAL;
public:
    Enemy_Interface(const int& index)
        :m_EnemyIndex(index) {}
    
    int GetMaxHp()const { return m_MaxHp; }
    int GetHp()const { return m_Hp; }    
    int GetEnemyIndex()const { return m_EnemyIndex; }
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
        if (m_MaxHp == hp) {
            return false;
        }        
        m_MaxHp = hp;
        SetHp(hp);
        return true;
    }
    void SetIndex(const int& index) { 
        if (m_EnemyIndex < 0 || m_EnemyIndex >= ENEMY_MAX) {
            m_EnemyIndex = ENEMY_NORMAL;
        }
        m_EnemyIndex = index; 
    }

    void CollosionWithBullet()
    {
        m_Hp--;

        if (m_Hp <= 0) {
            for (int i = 0; i < 30; i++) {
                Manager::GetScene()->
                    GetGameObject< ParticleObject>()->
                    SetParticle_Preset2(m_Position);
            }
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

    virtual void Init() {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);
          
        AddComponent<StageLimitComponent>(COMLAYER_SECOND);

        SetHp(GetMaxHp());

        AddComponent< ImGuiComponent>(COMLAYER_SECOND)->SetEnemyVersion();

        ComponentObject::Init();
    }
};

