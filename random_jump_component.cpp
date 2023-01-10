#include "random_jump_component.h"
#include "velocity_component.h"
#include "count_component.h"
#include "player.h"
void RandomJumpComponent::Init()
{
	m_Velociy = m_Parent->GetComponents<VelocityComponent>();
	m_Count = m_Parent->AddComponent<CountComponent>(COMLAYER_SECOND);
}

void RandomJumpComponent::Uninit()
{

}

void RandomJumpComponent::Update()
{
	if (m_Count->GetInFinist())
	{
		m_Count->Start(false, JUMP_INTERVAL, 0);

		for (auto vel : m_Velociy)
		{
			vel->m_Velocity.y = ENEMY_JUMP_VALUE;
			break;
		}
	}

	if (m_Count->GetFinish())
	{
		m_Count->Start(true, JUMP_INTERVAL, 0);

		for (auto vel : m_Velociy)
		{
			vel->m_Velocity.y = ENEMY_JUMP_VALUE;
			break;
		}
	}
}

void RandomJumpComponent::Draw()
{

}

void RandomJumpComponent::DrawImgui()
{
}