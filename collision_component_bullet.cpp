#include "collision_component_bullet.h"
#include "enemy.h"
#include "effect_explosion.h"
#include "particle_object.h"

void CollisionComponent_Bullet::Update()
{
	std::vector<GameObject*> enemys = IsCollisionCube_Enemy(LAYER_ENEMY);
	for (auto enemy : enemys) {
		dynamic_cast<Enemy_Interface*>(enemy)->CollosionWithBullet();


		m_Parent->SetDestroy();


		m_Scene->AddGameObject<Effect_explosion>
			(LAYER_3D)->SetPosition(m_Parent->GetPosition());

		int this_enemy_hp = dynamic_cast<Enemy_Interface*>(enemy)->GetHp();
		int particle_num = 10;

		switch (this_enemy_hp)
		{
		case 0:
			particle_num = 200;
			break;
		case 1:
			particle_num = 50;
			break;
		case 2:
			particle_num = 25;
			break;
		default:
			particle_num = 10;
			break;
		}

		for (int i = 0; i < particle_num; i++) {
			m_Scene->GetGameObject< ParticleObject>()
				->SetParticle_EnemyCollision(enemy->GetPosition(), this_enemy_hp);
		}
		break;
	}
}

std::vector<GameObject*> CollisionComponent_Bullet::IsCollisionCube_Enemy(const int& Layer)
{
	std::vector<GameObject*> m_GameObjects;
	std::vector<GameObject*> ResultObjects;
	m_GameObjects = m_Scene->GetGameObjectLayer(Layer);
	for (auto object : m_GameObjects) {
		D3DXVECTOR3 objectPosition = object->GetPosition();
		D3DXVECTOR3 parentPosition = m_Parent->GetPosition();
		D3DXVECTOR3 objectScale = object->GetScale();
		D3DXVECTOR3 parentScale = m_Parent->GetScale();

		if (objectPosition.x + objectScale.x / 6.0f > parentPosition.x - parentScale.x &&
			objectPosition.x - objectScale.x / 6.0f <= parentPosition.x + parentScale.x &&
			objectPosition.y + objectScale.y * 3.5f >= parentPosition.y - parentScale.y &&
			objectPosition.y - objectScale.y < parentPosition.y + parentScale.y &&
			objectPosition.z + objectScale.z / 6.0f >= parentPosition.z - parentScale.z &&
			objectPosition.z - objectScale.z / 6.0f < parentPosition.z + parentScale.z) {
			ResultObjects.push_back(object);
		}
	}

	return ResultObjects;
}
