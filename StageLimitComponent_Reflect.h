#pragma once
#include "StageLimitComponent.h"

class StageLimitComponent_Reflect : public StageLimitComponent
{
private:
    float m_YMin = 0.0f;
public:
    void SetYmin(const float& min) { m_YMin = min; }
    float GetYmin() { return m_YMin; }

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

        if (parent_pos.y > Y_MAX ||
            parent_pos.y <= m_YMin) {
            for (auto vel : m_Velocities) {
                vel->m_Velocity.y = 0.0f;
                  vel->SetOldPos('y',m_YMin);                
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