#include "collision_component_player.h"

#include "enemy_interface.h"
#include "effect_explosion.h"
#include "hp_component.h"
#include "particle_object_2d.h"
#include "co_stand.h"
#include "hp_component.h"
#include "count_component.h"

void CollisionComponent_Player::Init()
{
    CollisionComponent::Init();
    m_Count = m_Parent->AddComponent<CountComponent>(COMLAYER_SECOND);
}

void CollisionComponent_Player::Update() 
{

    if (m_IsGenerateMode)return;

    if (m_Count->GetFinish()) {
        m_IsCollision = true;
    }

    if (m_IsCollision == false)return;

    // 衝突しているエネミー取得
    std::vector<GameObject*> enemys = IsCollisionSphere(LAYER_ENEMY);

    // プレイヤーのhp取得
    HPComponent* hp = m_Parent->GetComponent<HPComponent>();

    // 衝突しているエネミーがいれば
    for (auto enemy : enemys) 
    {
        m_Count->Start(false, NO_COLL_TIME, 0);
        m_IsCollision = false;

        dynamic_cast<Enemy_Interface*>(enemy)->CollosionWithBullet();

        //enemy->SetDestroy();

        m_Parent->GetComponent<HPComponent>()->TakeDamage(2);

        m_Scene->AddGameObject<Effect_explosion>
            (LAYER_3D)->SetPosition(m_Parent->GetPosition());

        // 3Dパーティクル
        for (int i = 0; i < 5; i++) {
            m_Scene->GetGameObject< ParticleObject>()
                ->SetParticle_Preset1(m_Parent->GetPosition());
        }

        SetParticle2D(hp);

        break;
    }
}

void CollisionComponent_Player::DrawImgui()
{
    ImGui::Checkbox("Is Player Collision", &m_IsCollision);
}

std::vector<GameObject*> CollisionComponent_Player::IsCollisionSphere(const int& Layer)
{
    std::vector<GameObject*> m_GameObjects;
    std::vector<GameObject*> ResultObjects;
    m_GameObjects = m_Scene->GetGameObjectLayer(Layer);
    for (auto object : m_GameObjects) {
        D3DXVECTOR3 objectPosition = object->GetPosition();
        D3DXVECTOR3 direction = m_Parent->GetPosition() - objectPosition;
        float length = D3DXVec3Length(&direction);

        if (length < object->GetLength() + m_Parent->GetLength()) {
            ResultObjects.push_back(object);
        }
    }

    return ResultObjects;
}

void CollisionComponent_Player::SetParticle2D(HPComponent* hp)
{
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
}
