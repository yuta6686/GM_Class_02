#pragma once
#include "Component.h"
#include "VelocityComponent.h"

class StageLimitComponent :
    public Component
{
private:
    std::vector<VelocityComponent*> m_Velocities;

    inline static const float X_MAX = 23.5f;
    inline static const float X_MIN = -19.5f;

    inline static const float Y_MAX = 100.0f;   
    //  ‰º•ûŒü‚ÌŒÀŠE‚Í‘¼‚Å‚â‚Á‚Ä‚é‚Ì‚Å‚â‚ç‚È‚¢

    inline static const float Z_MAX = 42.0f;
    inline static const float Z_MIN = -37.5f;
public:   
    virtual void Init() override
    {
        m_Velocities = m_Parent->GetComponents<VelocityComponent>();
    }
    virtual void Uninit() override
    {
    }
    virtual void Update() override
    {
        D3DXVECTOR3 parent_pos = m_Parent->GetPosition();
        if (parent_pos.x > X_MAX ||
            parent_pos.x < X_MIN ) {

            for (auto vel : m_Velocities) {
                vel->m_Velocity.x = 0.0f;
                vel->SetOldPos('x');
            }
        }

        if (parent_pos.y > Y_MAX) {
            for (auto vel : m_Velocities) {
                vel->m_Velocity.y = 0.0f;
                vel->SetOldPos('y');
            }
        }
        if (parent_pos.z > Z_MAX ||
            parent_pos.z < Z_MIN) {
            for (auto vel : m_Velocities) {
                vel->m_Velocity.z = 0.0f;
                vel->SetOldPos('z');
            }
        }
    }
    virtual void Draw() override
    {
    }
    virtual void DrawImgui() override
    {
    }
};

