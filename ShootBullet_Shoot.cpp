#include "ShootBullet_Shoot.h"
#include "ShootBullet_Idle.h"
#include "Bullet.h"
#include "GameScene.h"
#include "manager.h"
#include "player.h"
#include "audio.h"
#include "UI_Charge.h"
#include "UI_Score.h"

//	�����d��������Astatic bool flag��p�ӂ��āAstatic �֐��ŃQ�[���V�[���ɓ��邽�т�
//	flag��߂��B
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
	if (m_Counter >= 10) {
		m_Counter = 0;
		m_BulletNum--;

		m_Bullet = m_Scene->AddGameObject<Bullet>(LAYER_3D);

		//	�����Z�b�g
		D3DXVECTOR3 rot = m_Player->GetCameraRot(), rrot = rot;
		rot.x = rrot.y;
		rot.y = rrot.x;
		rot.z = rrot.z;

		//	�Z�b�g
		D3DXVECTOR3 offset = { 0.0f,1.0f,0.0f };
		m_Bullet->SetPosition(m_Player->GetPosition() + offset);
		m_Bullet->SetRotation(rot);
		m_Bullet->SetForward(m_Player->GetCameraForward());
		float value = (logf(m_BulletNum + 2)*2.0f);
		m_Bullet->SetSpeed(value);
		float scale = value * 2.0f;
		m_Bullet->SetScale({ scale,scale,scale });

		m_Player->GetShootSE()->Play(false);
						

		if (m_BulletNum <= 0) {
			m_IsNextState = true;
		}

		std::shared_ptr<Scene> scene = Manager::GetScene();
		scene->GetGameObject<UI_Score>()->AddCount(1);
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