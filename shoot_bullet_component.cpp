#include "shoot_bullet_component.h"
#include "shoot_bullet_idle.h"

void ShootBulletComponent::Init()
{
	m_ShootBullet = new ShootBullet_Idle();
	m_ShootBullet->Init();
}

void ShootBulletComponent::Uninit()
{
	m_ShootBullet->Uninit();
	delete m_ShootBullet;
}

void ShootBulletComponent::Update()
{
	if (!m_IsUseBullet)return;

	m_ShootBullet->Update();

	if (m_ShootBullet->GetIsNextState()) {
		//	����state�̃|�C���^�������炤�B
		ShootBullet* sb = m_ShootBullet->CreateNextState();

		//	���̃|�C���^�͏����B
		m_ShootBullet->Uninit();
		delete m_ShootBullet;

		//	�V�����|�C���^�����
		m_ShootBullet = sb;
		m_ShootBullet->Init();
	}
}

void ShootBulletComponent::Draw()
{
}

void ShootBulletComponent::DrawImgui()
{
	ImGui::Checkbox("IsUseBullet", &m_IsUseBullet);
}