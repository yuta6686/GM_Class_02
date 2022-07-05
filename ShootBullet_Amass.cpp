#include "ShootBullet_Amass.h"
#include "ShootBullet_Shoot.h"
#include "UI_Charge.h"
#include "GameScene.h"
#include "manager.h"

void ShootBullet_Amass::Init()
{
	m_BulletNum = 0;
	m_Counter = 0;

	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_uiCharge = scene->GetGameObject<UI_Charge>();
}

void ShootBullet_Amass::Uninit()
{
	m_uiCharge->SetIsDecrease(true);
}

void ShootBullet_Amass::Update()
{
	if (IsMouseLeftPressed()) {
		m_Counter++;
		if (m_Counter % 10 == 0) {
			m_BulletNum++;
		}

		m_uiCharge->SetCounter((float)m_Counter);
	}
	else {
		m_IsNextState = true;
	}
}

void ShootBullet_Amass::Draw()
{
#ifdef _DEBUG
	char* str = GetDebugStr();
	wsprintf(GetDebugStr(), "game");
	wsprintf(&str[strlen(str)], "Amass");

	SetWindowText(GetWindow(), GetDebugStr());
#endif
}

ShootBullet* ShootBullet_Amass::CreateNextState()
{
    return new ShootBullet_Shoot(m_BulletNum);
}
