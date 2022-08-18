#pragma once
#include "StageLimitComponent.h"

class StageLimitComponent_Reflect : public StageLimitComponent
{
public:
	virtual void Init()override
	{
		StageLimitComponent::Init();
	}

	virtual void Update()override
	{
        D3DXVECTOR3 parent_pos = m_Parent->GetPosition();
        if (parent_pos.x > X_MAX ||
            parent_pos.x < X_MIN) {

            for (auto vel : m_Velocities) {
                vel->m_Velocity.x *= -1.0f;                
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
                vel->m_Velocity.z *= -1.0f;
                vel->SetOldPos('z');
            }
        }
	}
};