#include "ShootBullet_Shoot.h"
#include "ShootBullet_Idle.h"
#include "Bullet.h"
#include "GameScene.h"
#include "manager.h"
#include "player.h"
#include "audio.h"
#include "UI_Charge.h"
#include "UI_Score.h"

using namespace std;

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
	if (m_Counter >= 10) {
		m_Counter = 0;
		m_BulletNum--;

		m_Bullet = m_Scene->AddGameObject<Bullet>(LAYER_3D);

		//	方向セット
		D3DXVECTOR3 rot = m_Player->GetCameraRot(), rrot = rot;
		rot.x = rrot.y;
		rot.y = rrot.x;
		rot.z = rrot.z;

		//	セット
		D3DXVECTOR3 offset = { 0.0f,2.5f,0.0f };
		m_Bullet->SetPosition(m_Player->GetPosition() + offset);
		m_Bullet->SetRotation(rot);
		
		float speed = static_cast<float>(m_BulletNum + 2);
		
		float scale = speed * 2.0f;

		m_Bullet->Shoot(m_Player->GetCameraForward(), speed);
		m_Bullet->SetScale({ scale,scale,scale });


		m_Player->GetShootSE()->Play(false);
		m_Player->GetShootSE()->SetAudioVolume(0.2f);


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

	ImGui::Text("Shoot");
	ImGui::Text("Bullet Num:%d", m_BulletNum);

#endif // _DEBUG
}

ShootBullet* ShootBullet_Shoot::CreateNextState()
{
	return new ShootBullet_Idle();
}
