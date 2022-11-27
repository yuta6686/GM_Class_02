#include "stdafx.h"
#include "gravity_component.h"
#include "player.h"

void GravityComponent::Init()
{
	// todo: シングルトン化する
	m_Velocity = m_Parent->GetComponents<VelocityComponent>();
}
void GravityComponent::Update()
{
	for (auto vel : m_Velocity)
	{
		vel->m_Velocity.y -= Player::GetGravity();
		break;
	}
}