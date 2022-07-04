#include "ShootBullet_Shoot.h"
#include "ShootBullet_Idle.h"
#include "Bullet.h"
#include "GameScene.h"
#include "manager.h"
#include "player.h"
#include "audio.h"

//	もし重かったら、static bool flagを用意して、static 関数でゲームシーンに入るたびに
//	flagを戻す。
void ShootBullet_Shoot::Init()
{
	 m_Scene = Manager::GetScene();

	m_Player = m_Scene->GetGameObject<Player>();
}

void ShootBullet_Shoot::Uninit()
{
}

void ShootBullet_Shoot::Update()
{
	m_Counter++;
	if (m_Counter >= 5) {
		m_Counter = 0;
		m_BulletNum--;

		m_Bullet = m_Scene->AddGameObject<Bullet>(LAYER_3D);

		D3DXVECTOR3 rot = m_Player->GetCameraRot(), rrot = rot;
		rot.x = rrot.y;
		rot.y = rrot.x;
		rot.z = rrot.z;

		//	セット
		D3DXVECTOR3 offset = { 0.0f,1.0f,0.0f };
		m_Bullet->SetPosition(m_Player->GetPosition() + offset);
		m_Bullet->SetRotation(rot);
		m_Bullet->SetForward(m_Player->GetCameraForward());
		float value = (m_BulletNum + 2) * 2.0f;
		m_Bullet->SetSpeed(value);
		m_Bullet->SetScale({ value,value,value});

		m_Player->GetShootSE()->Play(false);



		if (m_BulletNum <= 0) {
			m_IsNextState = true;
		}

		
	}	
}

void ShootBullet_Shoot::Draw()
{
#ifdef _DEBUG
	char* str = GetDebugStr();
	wsprintf(GetDebugStr(), "game");
	wsprintf(&str[strlen(str)], "Shoot");

	SetWindowText(GetWindow(), GetDebugStr());
#endif
}

ShootBullet* ShootBullet_Shoot::CreateNextState()
{
    return new ShootBullet_Idle();
}
