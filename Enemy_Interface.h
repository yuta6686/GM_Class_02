#pragma once
#include "ComponentObject.h"
#include "TrackingComponent.h"
#include "StageLimitComponent_Reflect.h"
#include "CollisionComponent_Enemy.h"
#include "GravityComponent.h"
#include "CountComponent.h"

#include "ParticleObject.h"
#include "audio.h"
enum ENEMY
{
    ENEMY_NORMAL,
    ENEMY_TRACKING,
    ENEMY_TRACKING_FAST,
    ENEMY_TRACKING_LATE,
    ENEMY_NO_DRUM,
    ENEMY_MOVE_STRAIGHT,
    ENEMY_JUMP,
    ENEMY_BOSS,
    ENEMY_MAX
};
class Enemy_Interface :
    public ComponentObject
{
private:
    class Audio* m_SEEnemyCollision;
    class Audio* m_SEEnemyKill;
protected:    
    int m_MaxHp=1;
    int m_Hp = m_MaxHp;
    static const int MAX_HP = 9999;
    int m_EnemyIndex = ENEMY_NORMAL;
    CountComponent* m_Count;
    D3DXVECTOR3 m_FirstScale;
    bool m_IsDestroy = false;
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

    void SetFirstScale(const D3DXVECTOR3& scale)
    {
        m_FirstScale = scale;
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
            m_IsDestroy = true;
            //SetDestroy();
            m_SEEnemyKill->Play(false);
        }
        else {
            m_SEEnemyCollision->Play(false);
        }

    } 

    virtual void Init() {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        AddComponent<VelocityComponent>(COMLAYER_SECOND);        
                 
        AddComponent<StageLimitComponent_Reflect>(COMLAYER_MATRIX);

        AddComponent<CollisionComponent_Enemy>(COMLAYER_SECOND);

        SetHp(GetMaxHp());

        m_Count = AddComponent< CountComponent>(COMLAYER_SECOND);
        m_Count->Start(false, 60, 0);

        AddComponent< ImGuiComponent>(COMLAYER_SECOND)->SetEnemyVersion();

        ComponentObject::Init();

        m_FirstScale = m_Scale;

        std::shared_ptr<Scene> scene = Manager::GetScene();
        m_SEEnemyCollision = scene->AddGameObject<Audio>(LAYER_AUDIO);
        m_SEEnemyCollision->Load("asset\\audio\\SE_EnemyCollision.wav");
        m_SEEnemyKill = scene->AddGameObject<Audio>(LAYER_AUDIO);
        m_SEEnemyKill->Load("asset\\audio\\SE_EnemyKill.wav");

    }

    virtual void Update()
    {


        if (m_IsDestroy && m_Count->GetFinish()) {
            m_Count->Start(true, 15, 0);
        }

        if (m_Count->GetInFinist()) {
            SetDestroy();
        }
        
        m_Scale = m_FirstScale *  m_Count->Get0to1Count();

        ComponentObject::Update();
    }

    virtual void Draw()
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

        ComponentObject::Draw();
    }
};

