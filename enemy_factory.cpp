#include "stdafx.h"
#include "enemy_factory.h"
#include "Enemy_Interface.h"
#include "cylinder.h"

Enemy_Interface* EnemyFactory::Create(const int& hp, const int& index)
{
	std::shared_ptr<Scene> m_Scene = Manager::GetScene();
	Enemy_Interface* penemy = nullptr;
	switch (index)
	{
	case ENEMY_NORMAL:
		penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
		break;
	case ENEMY_TRACKING:
		penemy = m_Scene->AddGameObject<Enemy_Tracking>(LAYER_ENEMY);
		break;
	case ENEMY_TRACKING_FAST:
		penemy = m_Scene->AddGameObject<Enemy_Tracking_Fast>(LAYER_ENEMY);
		break;
	case ENEMY_TRACKING_LATE:
		penemy = m_Scene->AddGameObject<Enemy_Tracking_Late>(LAYER_ENEMY);
		break;

	case ENEMY_NO_DRUM:
		// TODO Œã‚Å’u‚«Š·‚¦‚é
		penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
		break;
	case ENEMY_MOVE_STRAIGHT:
		penemy = m_Scene->AddGameObject<Enemy_Move_Straight>(LAYER_ENEMY);
		break;
	case ENEMY_JUMP:
		penemy = m_Scene->AddGameObject<Enemy_Jump>(LAYER_ENEMY);
		break;
	case ENEMY_BOSS:
		penemy = m_Scene->AddGameObject<Enemy_Boss>(LAYER_ENEMY);
		break;
	case ENEMY_MAX:
		penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
		break;
	default:
		penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
		break;
	}

	penemy->SetHp(hp);
	
	return penemy;
}