#include "shoot_bullet_amass.h"
#include "shoot_bullet_shoot.h"
#include "ui_charge.h"
#include "player.h"

#include "game_scene.h"


void ShootBullet_Amass::Init()
{
	m_BulletNum = 0;
	m_Counter = 0;

	m_Scene = Manager::GetScene();

	// ToDo後でシングルトンにしよう
	// 多分AddGameObjectでシングルトンフラグをデフォルトでつけて
	// GetGameObject<T>でnullptrなら新しく作る
	// すでにあったらそれを返す。
	auto ui_charge = m_Scene->GetGameObject<UI_Charge>();
	if (ui_charge == nullptr) 
		m_uiCharge = m_Scene->AddGameObject<UI_Charge>(LAYER_2D);
	else
		m_uiCharge = ui_charge;
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
			if (m_BulletNum >= 20) {
				m_IsNextState = true;
			}
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
