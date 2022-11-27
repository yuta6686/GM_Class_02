#include "stdafx.h"
#include "tracking_component.h"

#include "player.h"
#include "velocity_component.h"

void TrackingComponent::Init()
{
	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_Target = scene->GetGameObject<Player>();

	//  Velocityコンポーネントとして実装
	m_VelocityComponent = m_Parent->GetComponent<VelocityComponent>();
}

void TrackingComponent::Uninit()
{
}

void TrackingComponent::Update()
{
	const D3DXVECTOR3 targetpos = m_Target->GetPosition();
	const D3DXVECTOR3 enemypos = m_Parent->GetPosition();

	//  エネミーからプレイヤーへの長さ
	D3DXVECTOR3 direction = targetpos - enemypos;

	//  正規化　向きを取る　(-1.0f ～ 1.0f）
	D3DXVec3Normalize(&direction, &direction);

	m_VelocityComponent->m_Velocity = direction * m_Speed;

	//m_Parent->SetRotation({ acosf(direction.x),asinf(direction.y),asinf(direction.z) });
	m_Parent->SetRotation({ acosf(direction.x),0.0f,0.0f });

	//  Velocityコンポーネントとして実装
	//m_Parent->SetPosition(enemypos + m_VelocityComponent->m_Velocity);
}

void TrackingComponent::Draw()
{
}

void TrackingComponent::DrawImgui()
{
	ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 0.5f, "%.2f");
}
