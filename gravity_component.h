#pragma once
#include "component.h"
#include "VelocityComponent.h"
#include "player.h"

class GravityComponent :
    public Component
{
private:
    std::vector<VelocityComponent*> m_Velocity;
public:
    
    virtual void Init() override
    {
        m_Velocity = m_Parent->GetComponents<VelocityComponent>();
    }
    virtual void Uninit() override
    {
    }
    virtual void Update() override
    {
        for (auto vel : m_Velocity)
        {
            vel->m_Velocity.y -= Player::GetGravity();
            break;
        }
    }
    virtual void Draw() override
    {
    }
    virtual void DrawImgui() override
    {
    }
};

