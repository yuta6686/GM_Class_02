#pragma once
#include "Component.h"
#include "gameObject.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "VelocityComponent.h"

class TrackingComponent :
    public Component
{
private:
    GameObject* m_Target;

    //  Velocity�R���|�[�l���g�Ƃ��Ď���    
    VelocityComponent* m_VelocityComponent;

    float m_Speed = 0.1f;
public:
    void SetSpeed(const float& speed) { m_Speed = speed; }
    float GetSpeed()const { return m_Speed; }

    virtual void Init() override
    {
        std::shared_ptr<Scene> scene = Manager::GetScene();
        m_Target = scene->GetGameObject<Player>();

        //  Velocity�R���|�[�l���g�Ƃ��Ď���        
        m_VelocityComponent = m_Parent->GetComponent<VelocityComponent>();
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

        m_VelocityComponent->m_Velocity = direction * m_Speed;
        

        //m_Parent->SetRotation({ acosf(direction.x),asinf(direction.y),asinf(direction.z) });
        m_Parent->SetRotation({ acosf(direction.x),0.0f,0.0f });


        //  Velocity�R���|�[�l���g�Ƃ��Ď���
        //m_Parent->SetPosition(enemypos + m_VelocityComponent->m_Velocity);
    }

    virtual void Draw() override
    {
    }

    virtual void DrawImgui() override
    {
        ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 0.5f, "%.2f");
    }

};

