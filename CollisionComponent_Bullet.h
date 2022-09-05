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
        std::vector<GameObject*> enemys = IsCollisionCube_Enemy(LAYER_ENEMY);
        for (auto enemy : enemys) {
            dynamic_cast<Enemy_Interface*>(enemy)->CollosionWithBullet();            


            m_Parent->SetDestroy();


            m_Scene->AddGameObject<Effect_explosion>
                (LAYER_3D)->SetPosition(m_Parent->GetPosition());

            int this_enemy_hp = dynamic_cast<Enemy_Interface*>(enemy)->GetHp();
            int particle_num = 10;

            switch (this_enemy_hp)
            {
            case 0:
                particle_num = 200;
                break;
            case 1:
                particle_num = 50;
                break;
            case 2:
                particle_num = 25;
                break;
            default:
                particle_num = 10;
                break;
            }

            for (int i = 0; i < particle_num; i++) {
                m_Scene->GetGameObject< ParticleObject>()
                    ->SetParticle_EnemyCollision(enemy->GetPosition(),this_enemy_hp);
            }
            break;
        }        
    }
};

