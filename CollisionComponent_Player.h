#pragma once
#include "CollisionComponent.h"
#include "Enemy_Interface.h"
#include "effect_explosion.h"
#include "HPComponent.h"
class CollisionComponent_Player :
    public CollisionComponent
{
public:
    virtual void Update() override
    {
        std::vector<GameObject*> enemys = IsCollisionSphere(LAYER_ENEMY);
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
            break;
        }
    }
};

