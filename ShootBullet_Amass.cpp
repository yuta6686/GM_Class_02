#include "ShootBullet_Amass.h"
#include "ShootBullet_Shoot.h"

void ShootBullet_Amass::Init()
{
	m_BulletNum = 0;
	m_Counter = 0;
}

void ShootBullet_Amass::Uninit()
{
}

void ShootBullet_Amass::Update()
{
	if (IsMouseLeftPressed()) {
		m_Counter++;
		if (m_Counter % 10 == 0) {
			m_BulletNum++;
		}
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
