#include "stage_limit_component.h"

void StageLimitComponent::Init() 
{
	m_Velocities = m_Parent->GetComponents<VelocityComponent>();
}
void StageLimitComponent::Uninit() 
{
}
void StageLimitComponent::Update() 
{
	D3DXVECTOR3 parent_pos = m_Parent->GetPosition();
	if (parent_pos.x > X_MAX ||
		parent_pos.x < X_MIN) {
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

void StageLimitComponent::Draw()
{
}

void StageLimitComponent::DrawImgui()
{
}
