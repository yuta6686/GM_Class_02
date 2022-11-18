#include "shoot_bullet_idle.h"
#include "shoot_bullet_amass.h"

void ShootBullet_Idle::Init()
{
}

void ShootBullet_Idle::Uninit()
{

}

void ShootBullet_Idle::Update()
{
	if (IsMouseLeftTriggered()) {
		m_IsNextState = true;
	}
}

void ShootBullet_Idle::Draw()
{	
#ifdef _DEBUG

	ImGui::Text("Idle");
	ImGui::Text("Bullet Num:0");

#endif // _DEBUG
}

ShootBullet* ShootBullet_Idle::CreateNextState()
{
	return new ShootBullet_Amass();
}

void ShootBullet_Idle::DrawImgui()
{
}
