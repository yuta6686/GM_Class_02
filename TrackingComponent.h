#pragma once
#include "Component.h"
#include "gameObject.h"
#include "scene.h"
#include "manager.h"
#include "player.h"

class TrackingComponent :
    public Component
{
private:
    GameObject* m_Target;

    //  Velocity�R���|�[�l���g�Ƃ��Ď���
    D3DXVECTOR3 m_Velocity;
public:

    virtual void Init() override
    {
        std::shared_ptr<Scene> scene = Manager::GetScene();
        m_Target = scene->GetGameObject<Player>();

        //  Velocity�R���|�[�l���g�Ƃ��Ď���
        m_Velocity = { 0.0f,0.0f,0.0f };
    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {        
        const D3DXVECTOR3 targetpos = m_Target->GetPosition();
        const D3DXVECTOR3 enemypos = m_Parent->GetPosition();        

        //  �G�l�~�[����v���C���[�ւ̒���
        D3DXVECTOR3 direction = targetpos - enemypos;      

        

        //  ���K���@���������@(-1.0f �` 1.0f�j
        D3DXVec3Normalize(&direction, &direction);

        m_Velocity = direction * 0.1f;

        //m_Parent->SetRotation({ acosf(direction.x),asinf(direction.y),asinf(direction.z) });
        m_Parent->SetRotation({ acosf(direction.x),0.0f,0.0f });


        //  Velocity�R���|�[�l���g�Ƃ��Ď���
        m_Parent->SetPosition(enemypos + m_Velocity);
    }

    virtual void Draw() override
    {
    }

    virtual void DrawImgui() override
    {
    }

};

