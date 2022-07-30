#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "field.h"
#include "model.h"
#include "input.h"
#include "bullet.h"
#include "scene.h"
#include "manager.h"
#include "ResourceManager.h"
#include "effect_explosion.h"
#include "player.h"
#include "Enemy.h"

void Bullet::Update()
{
	std::shared_ptr<Scene> scene = Manager::GetScene();	
	
	

	//	エネミー取得	
	std::vector<Enemy*> enemyList
		= scene->GetGameObjects<Enemy>();

	//	エネミーとの当たり判定
	for (auto enemy : enemyList) {
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();
		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 4.0f) {
			enemy->CollosionWithBullet();
			this->SetDestroy();
			scene->AddGameObject<Effect_explosion>(LAYER_3D)->SetPosition(m_Position);
			return;
		}
	}

	ComponentObject::Update();
}
