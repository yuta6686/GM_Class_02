#pragma once
#include "CollisionComponent.h"
#include "Enemy_Interface.h"
#include "effect_explosion.h"
#include "HPComponent.h"
#include "ParticleObject_2D.h"
#include "CO_Stand.h"
#include "HPComponent.h"
class CollisionComponent_Player :
    public CollisionComponent
{
public:
    virtual void Update() override
    {
        std::vector<GameObject*> enemys = IsCollisionSphere(LAYER_ENEMY);
        HPComponent* hp = m_Parent->GetComponent<HPComponent>();

        for (auto enemy : enemys) {
            dynamic_cast<Enemy_Interface*>(enemy)->CollosionWithBullet();

            enemy->SetDestroy();
            
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
};
