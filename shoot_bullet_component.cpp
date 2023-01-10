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
		//	次のstateのポインタだけもらう。
		ShootBullet* sb = m_ShootBullet->CreateNextState();

		//	今のポインタは消す。
		m_ShootBullet->Uninit();
		delete m_ShootBullet;

		//	新しいポインタを作る
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