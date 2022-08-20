#pragma once
#include "ComponentObject.h"
#include "Enemy.h"
#include "manager.h"
#include "Cylinder.h"

#include <fstream>
#include <iostream>
#include <sstream>

enum ENEMY_WAVE {
	EW_1_1 = 0,
	EW_1_2,
	EW_1_3,
	EW_2_1,
	EW_2_2,
	EW_2_3,
	EW_3_1,
	EW_3_2,
	EW_3_3,
	EW_MAX,
};
class EnemyWave :
	public GameObject
{
protected:
	std::shared_ptr<Scene> m_Scene;
	std::vector<GameObject*> m_EnemyList;
	std::vector<Enemy_Tracking*> m_EnemyTrackingList;
	std::vector<Enemy_Tracking_Fast*> m_EnemyFastList;
	std::vector<Enemy_Tracking_Late*> m_EnemyLateList;

	std::string m_StageFileName = "asset\\file\\EnemyGenerate1-1.txt";
	bool m_IsNextWave = false;
	bool m_IsTracking = false;
	int m_Index = EW_1_1;

	void LoadStageFile() {
		std::ifstream ifs(m_StageFileName.c_str());

		std::string str_buf;
		std::string str_conma_buf;
		std::vector<std::string> str_buf_vec;

		while (std::getline(ifs, str_buf)) {
			std::istringstream istream(str_buf);

			while (std::getline(istream, str_conma_buf, ',')) {
				str_buf_vec.push_back(str_conma_buf);
			}

			D3DXVECTOR3 pos;
			D3DXVECTOR3 rot;
			D3DXVECTOR3 sca;
			int hp = 1;
			int enemy_index = ENEMY_NORMAL;

			pos.x = stof(str_buf_vec[0]);
			pos.y = stof(str_buf_vec[1]);
			pos.z = stof(str_buf_vec[2]);

			rot.x = stof(str_buf_vec[3]);
			rot.y = stof(str_buf_vec[4]);
			rot.z = stof(str_buf_vec[5]);

			sca.x = stof(str_buf_vec[6]);
			sca.y = stof(str_buf_vec[7]);
			sca.z = stof(str_buf_vec[8]);
			hp = stoi(str_buf_vec[9]);
			enemy_index = stoi(str_buf_vec[10]);

			Enemy_Interface* penemy=nullptr;
			Cylinder* cly;

			switch (enemy_index)
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
				m_Scene->AddGameObject<Cylinder>(LAYER_3D);
				cly = m_Scene->AddGameObject<Cylinder>(LAYER_3D);
				cly->SetPosition(pos);
				cly->SetRotation(rot);
				cly->SetScale(sca);
				break;
			case ENEMY_MOVE_STRAIGHT:
				penemy = m_Scene->AddGameObject<Enemy_Move_Straight>(LAYER_ENEMY);
				break;

			case ENEMY_JUMP:
				penemy = m_Scene->AddGameObject<Enemy_Jump>(LAYER_ENEMY);
				break;
			case ENEMY_MAX:
				penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
				break;
			default:
				penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
				break;
			}

			if (penemy != nullptr) {
				penemy->SetPosition(pos);
				penemy->SetRotation(rot);
				penemy->SetScale(sca);
				penemy->SetMaxHp(hp);
				penemy->SetHp(hp);
			}

			//penemy->AddComponent<TrackingComponent>(COMLAYER_SECOND);

			str_buf_vec.clear();
		}
	}

public:

	EnemyWave(const std::string& filename, const int& Index)
		:m_StageFileName(filename),
		m_Index(Index) {}

	virtual void Init() override {
		m_Scene = Manager::GetScene();
		LoadStageFile();
	}

	virtual void Uninit() override
	{

	}

	virtual void Update() override
	{
		m_Scene = Manager::GetScene();

		m_IsNextWave = true;		
	

		m_EnemyList = m_Scene->GetGameObjectLayer(LAYER_ENEMY);		
		if (!m_EnemyList.empty())
		{
			m_IsNextWave = false;
		}
/*
		m_EnemyTrackingList = m_Scene->GetGameObjects<Enemy_Tracking>();
		if (!m_EnemyTrackingList.empty())
		{
			m_IsNextWave = false;
		}

		m_EnemyFastList = m_Scene->GetGameObjects<Enemy_Tracking_Fast>();
		if (!m_EnemyFastList.empty())
		{
			m_IsNextWave = false;
		}

		m_EnemyLateList = m_Scene->GetGameObjects<Enemy_Tracking_Late>();
		if (!m_EnemyLateList.empty())
		{
			m_IsNextWave = false;
		}*/		
	}

	virtual void Draw() override {

	}

	virtual bool GetIsNextWave()const { return m_IsNextWave; }
	virtual EnemyWave* CreateNextWave() = 0;

	void SetStageFileName(const std::string& file) { m_StageFileName = file; }
	int GetEnemyIndex()const { return m_Index; }
};

