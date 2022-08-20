#pragma once
#include "ComponentObject.h"
#include "TrackingComponent.h"
#include "StageLimitComponent_Reflect.h"
#include "CollisionComponent_Enemy.h"
#include "GravityComponent.h"

#include "ParticleObject.h"
enum ENEMY
{
    ENEMY_NORMAL,
    ENEMY_TRACKING,
    ENEMY_TRACKING_FAST,
    ENEMY_TRACKING_LATE,
    ENEMY_NO_DRUM,
    ENEMY_MOVE_STRAIGHT,
    ENEMY_JUMP,
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

    void SetDiffuse(const D3DXCOLOR& color) {
        ModelDrawComponent* mdc = GetComponent<ModelDrawComponent>();
        if(mdc!=nullptr)
            GetComponent<ModelDrawComponent>()->SetDiffuse(color);
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

    virtual void Init() {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        AddComponent<VelocityComponent>(COMLAYER_SECOND);

        AddComponent< GravityComponent>(COMLAYER_SECOND);
                 
        AddComponent<StageLimitComponent_Reflect>(COMLAYER_MATRIX);

        AddComponent<CollisionComponent_Enemy>(COMLAYER_SECOND);

        SetHp(GetMaxHp());

        AddComponent< ImGuiComponent>(COMLAYER_SECOND)->SetEnemyVersion();

        ComponentObject::Init();
    }

    virtual void Update()
    {
        if (m_Hp <= 1) {
            SetDiffuse({ 1.0f,0.5f,0.5f,1.0f });
        }
        else if (m_Hp <= 2 && m_Hp > 1) {
            SetDiffuse({ 1.0f,1.0f,0.5f,1.0f });
        }
        else {
            SetDiffuse({ 0.8f,1.0f,1.0f,1.0f });
        }
    }
};

