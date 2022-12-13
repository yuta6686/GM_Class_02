#include "enemy_interface.h"
#include "component_object.h"
#include "tracking_component.h"
#include "stage_limit_reflect_component.h"
#include "collision_component_enemy.h"
#include "gravity_component.h"
#include "count_component.h"
#include "texture_compoennt.h"

#include "particle_object.h"
#include "audio.h"

void Enemy_Interface::Init()
{
    AddComponent<TransformInit>(COMLAYER_FIRST);

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_ENEMY);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX);

    AddComponent<VelocityComponent>(COMLAYER_SECOND);

    AddComponent<StageLimitComponent_Reflect>(COMLAYER_MATRIX);

    AddComponent<CollisionComponent_Enemy>(COMLAYER_SECOND);

    SetHp(GetMaxHp());

    m_Count = AddComponent< CountComponent>(COMLAYER_SECOND);
    m_Count->Start(false, 60, 0);

    AddComponent< ImGuiComponent>(COMLAYER_SECOND)->SetEnemyVersion();

    AddComponent<TextureComponent>(COMLAYER_SHADER)
        ->SetTextureAndSlot("asset\\texture\\normalmap.png", 1,true);

    AddComponent<TextureComponent>(COMLAYER_SHADER)
        ->SetTextureAndSlot("asset\\texture\\pixelNoiseColor.png", 2,true);

    ComponentObject::Init();

    m_FirstScale = m_Scale;

    std::shared_ptr<Scene> scene = Manager::GetScene();
    m_SEEnemyCollision = scene->AddGameObject<Audio>(LAYER_AUDIO);
    m_SEEnemyCollision->Load("asset\\audio\\SE_EnemyCollision.wav");
    m_SEEnemyKill = scene->AddGameObject<Audio>(LAYER_AUDIO);
    m_SEEnemyKill->Load("asset\\audio\\SE_EnemyKill.wav");

}

void Enemy_Interface::Update()

{


    if (m_IsDestroy && m_Count->GetFinish()) {
        m_Count->Start(true, 15, 0);
    }

    if (m_Count->GetInFinist()) {
        SetDestroy();
    }

    m_Scale = m_FirstScale * m_Count->Get0to1Count();

    ComponentObject::Update();
}

void Enemy_Interface::Draw()
{
    if (_hp <= 1) {
        SetDiffuse({ 1.0f,0.5f,0.5f,1.0f });
    }
    else if (_hp <= 2 && _hp > 1) {
        SetDiffuse({ 1.0f,1.0f,0.5f,1.0f });
    }
    else {
        SetDiffuse({ 0.8f,1.0f,1.0f,1.0f });
    }

    ComponentObject::Draw();
}

bool Enemy_Interface::SetHp(const int& hp)
{
    if (hp < 0 || hp >= MAX_HP) {
        _hp = 1;
        return false;
    }
    _hp = hp;
    return true;
}

void Enemy_Interface::SetFirstScale(const D3DXVECTOR3& scale)
{
    m_FirstScale = scale;
}

bool Enemy_Interface::SetMaxHp(const int& hp)

{
    if (hp < 0 || hp >= MAX_HP) {
        _maxHp = 1;
        return false;
    }
    if (_maxHp == hp) {
        return false;
    }
    _maxHp = hp;
    SetHp(hp);
    return true;
}

void Enemy_Interface::SetIndex(const int& index)
{
    if (m_EnemyIndex < 0 || m_EnemyIndex >= ENEMY_MAX) {
        m_EnemyIndex = ENEMY_NORMAL;
    }
    m_EnemyIndex = index;
}

void Enemy_Interface::SetDiffuse(const D3DXCOLOR& color)
{
    ModelDrawComponent* mdc = GetComponent<ModelDrawComponent>();
    if (mdc != nullptr)
        GetComponent<ModelDrawComponent>()->SetDiffuse(color);
}

void Enemy_Interface::CollosionWithBullet()
{
    _hp--;

    if (_hp <= 0) {
        m_IsDestroy = true;
        //SetDestroy();
        m_SEEnemyKill->Play(false);
    }
    else {
        m_SEEnemyCollision->Play(false);
    }

}

