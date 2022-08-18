#pragma once
#include "Component.h"
#include "VelocityComponent.h"
class RandomVelocityComponent :
    public Component
{
private:
    float m_Speed = 1.0f;

    D3DXVECTOR3 m_RandomVector = { 1.0f,1.0f,1.0f };

    std::vector<VelocityComponent*> m_Velocities;
public:
    void SetSpeed(const float& speed)
    {
        m_Speed = speed;
    }

    virtual void Init() override
    {
        m_Velocities = m_Parent->GetComponents<VelocityComponent>();

        m_RandomVector = MyMath::VEC3Random(-1.0f, 1.0f);
        m_RandomVector.y = 0.0f;

        for (auto vel : m_Velocities)
        {
            vel->m_Velocity = m_RandomVector * m_Speed;
            break;
        }
    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {
        
    }

    virtual void Draw() override
    {
    }

    virtual void DrawImgui() override
    {
    }

};

