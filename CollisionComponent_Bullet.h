#pragma once
#include "CollisionComponent.h"
#include "Enemy.h"
#include "effect_explosion.h"
class CollisionComponent_Bullet :
    public CollisionComponent
{
public:
    virtual void Update() override
    {
        std::vector<Enemy*> enemys = IsCollisionSphere<Enemy>();
        for (auto enemy : enemys) {
            enemy->CollosionWithBullet();
            m_Parent->SetDestroy();
            m_Scene->AddGameObject<Effect_explosion>
                (LAYER_3D)->SetPosition(m_Parent->GetPosition());
        }        
    }
};

