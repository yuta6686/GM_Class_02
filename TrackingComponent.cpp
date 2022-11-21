#include "tracking_component.h"
#include "manager.h"
#include "player.h"
#include "velocity_component.h"

void TrackingComponent::Init()
{
	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_Target = scene->GetGameObject<Player>();

	//  Velocity�R���|�[�l���g�Ƃ��Ď���
	m_VelocityComponent = m_Parent->GetComponent<VelocityComponent>();
}

void TrackingComponent::Uninit()
{
}

void TrackingComponent::Update()
{
	const D3DXVECTOR3 targetpos = m_Target->GetPosition();
	const D3DXVECTOR3 enemypos = m_Parent->GetPosition();

	//  �G�l�~�[����v���C���[�ւ̒���
	D3DXVECTOR3 direction = targetpos - enemypos;

	//  ���K���@���������@(-1.0f �` 1.0f�j
	D3DXVec3Normalize(&direction, &direction);

	m_VelocityComponent->m_Velocity = direction * m_Speed;

	//m_Parent->SetRotation({ acosf(direction.x),asinf(direction.y),asinf(direction.z) });
	m_Parent->SetRotation({ acosf(direction.x),0.0f,0.0f });

	//  Velocity�R���|�[�l���g�Ƃ��Ď���
	//m_Parent->SetPosition(enemypos + m_VelocityComponent->m_Velocity);
}

void TrackingComponent::Draw()
{
}

void TrackingComponent::DrawImgui()
{
	ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 0.5f, "%.2f");
}