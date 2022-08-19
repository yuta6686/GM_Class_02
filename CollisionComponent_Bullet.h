#pragma once
#include "CollisionComponent.h"
#include "Enemy.h"
#include "effect_explosion.h"
#include "ParticleObject.h"
class CollisionComponent_Bullet :
    public CollisionComponent
{
public:
    virtual void Update() override
    {
        std::vector<GameObject*> enemys = IsCollisionCube(LAYER_ENEMY);
        for (auto enemy : enemys) {
            dynamic_cast<Enemy_Interface*>(enemy)->CollosionWithBullet();            


            m_Parent->SetDestroy();


            m_Scene->AddGameObject<Effect_explosion>
                (LAYER_3D)->SetPosition(m_Parent->GetPosition());

            for (int i = 0; i < 5; i++) {
                m_Scene->GetGameObject< ParticleObject>()
                    ->SetParticle_Preset1(enemy->GetPosition());
            }
            break;
        }        
    }
};

