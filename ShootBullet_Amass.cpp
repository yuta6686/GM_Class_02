#include "ShootBullet_Amass.h"
#include "ShootBullet_Shoot.h"
#include "UI_Charge.h"
#include "player.h"

#include "GameScene.h"
#include "manager.h"

void ShootBullet_Amass::Init()
{
	m_BulletNum = 0;
	m_Counter = 0;

	m_Scene = Manager::GetScene();
	m_uiCharge = m_Scene->GetGameObject<UI_Charge>();
}

void ShootBullet_Amass::Uninit()
{
	m_uiCharge->SetIsDecrease(true);
}

void ShootBullet_Amass::Update()
{
	if (IsMouseLeftPressed()) {
		
		if (m_Counter % 10 == 0) {
			m_BulletNum++;						
		}
		m_Counter++;
		m_uiCharge->SetCounter((float)m_Counter/10.0f);		
	}
	else {
		m_IsNextState = true;
	}
}

void ShootBullet_Amass::Draw()
{
#ifdef _DEBUG
	
	ImGui::Text("Amass");
	ImGui::Text("Bullet Num:%d", m_BulletNum);
	
#endif // _DEBUG
}

ShootBullet* ShootBullet_Amass::CreateNextState()
{
	m_Scene->GetGameObject<Player>()
		->GetComponent<MonochromeComponent>()
		->SetBulletNum(m_BulletNum);

    return new ShootBullet_Shoot(m_BulletNum,m_Counter);
}
