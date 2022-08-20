#pragma once
#include "Component.h"
#include "VelocityComponent.h"
#include "CountComponent.h"
#include "player.h"

class RandomJumpComponent :
    public Component
{
private:
    std::vector<VelocityComponent*> m_Velociy;
    CountComponent* m_Count;
    inline static const float ENEMY_JUMP_VALUE = 0.5f;
public:

    virtual void Init() override
    {
        m_Velociy = m_Parent->GetComponents<VelocityComponent>();
        m_Count = m_Parent->AddComponent<CountComponent>(COMLAYER_SECOND);
    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {
        if (m_Count->GetInFinist()) 
        {
            m_Count->Start(false, 180, 0);

            for (auto vel : m_Velociy)
            {
                vel->m_Velocity.y = ENEMY_JUMP_VALUE;
                break;
            }
        }

        if (m_Count->GetFinish()) 
        {
            m_Count->Start(true, 180, 0);

            for (auto vel : m_Velociy)
            {
                vel->m_Velocity.y = ENEMY_JUMP_VALUE;
                break;
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

