#pragma once
#include "collision_component.h"
#include "Enemy_Interface.h"
#include "effect_explosion.h"
#include "hp_component.h"
#include "ParticleObject_2D.h"
#include "co_stand.h"
#include "hp_component.h"
#include "count_component.h"
class CollisionComponent_Player :
    public CollisionComponent
{
private:
    bool m_IsCollision = true;
    bool m_IsGenerateMode = false;
    CountComponent* m_Count;
public:
    void SetIsCollision(bool flag) { m_IsCollision = flag; }
    void SetIsGenerateMode(bool flag) { m_IsGenerateMode = flag; }
    virtual void Init()override
    {
        CollisionComponent::Init();
        m_Count = m_Parent->AddComponent<CountComponent>(COMLAYER_SECOND);
    }
    virtual void Update() override
    {
        if (m_IsGenerateMode)return;

        if (m_Count->GetFinish()) {
            m_IsCollision = true;
        }

        if (m_IsCollision == false)return;

        std::vector<GameObject*> enemys = IsCollisionSphere(LAYER_ENEMY);
        HPComponent* hp = m_Parent->GetComponent<HPComponent>();

        

        for (auto enemy : enemys) {
            m_Count->Start(false, 60, 0);
            m_IsCollision = false;

            dynamic_cast<Enemy_Interface*>(enemy)->CollosionWithBullet();

            //enemy->SetDestroy();
            
            m_Parent->GetComponent<HPComponent>()->TakeDamage(2);

            m_Scene->AddGameObject<Effect_explosion>
                (LAYER_3D)->SetPosition(m_Parent->GetPosition());            

            for (int i = 0; i < 5; i++) {
                m_Scene->GetGameObject< ParticleObject>()
                    ->SetParticle_Preset1(m_Parent->GetPosition());
            }

            int loop = 100;
            D3DXVECTOR4 color = { 1.0f,1.0f,1.0f,1.0f };

            if (hp->GetHpRatio() >= 0.5f)
            {
                color = { 1.0f,1.0f,1.0f,1.0f };
                loop = 50;
            }
            else if (hp->GetHpRatio() < 0.5f &&
                hp->GetHpRatio() >= 0.3f) {
                color = { 1.0f,0.0f,1.0f,1.0f };
                loop = 100;
            }
            else
            {
                color = { 1.0f,0.0f,0.0f,1.0f };
                loop = 300;
            }

            for (int i = 0; i < loop; i++)
                m_Scene->GetGameObject< ParticleObject_2D>()->SetParticle_Gather(color);
           
            break;
        }        
    }

    void DrawImgui()
    {
        ImGui::Checkbox("Is Player Collision", &m_IsCollision);
    }
};

