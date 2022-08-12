#pragma once
#include "ComponentObject.h"
#include "Enemy.h"
#include "manager.h"

#include <fstream>
#include <iostream>
#include <sstream>
class EnemyWave :
    public GameObject
{
protected:
    std::shared_ptr<Scene> m_Scene;
	std::vector<Enemy*> m_EnemyList;
    std::string m_StageFileName = "asset\\file\\EnemyGenerate2.txt";    
    bool m_IsNextWave = false;
	bool m_IsTracking = false;


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

			auto* penemy = m_Scene->AddGameObject<Enemy>(LAYER_3D);

			penemy->SetPosition(pos);
			penemy->SetRotation(rot);
			penemy->SetScale(sca);
			penemy->SetMaxHp(hp);
			penemy->SetHp(hp);

			penemy->AddComponent<TrackingComponent>(COMLAYER_SECOND);

			str_buf_vec.clear();
		}
    }

public:    

    EnemyWave(const std::string& filename) :m_StageFileName(filename) {}
	EnemyWave(const std::string& filename, const bool& isTracking)
		:m_StageFileName(filename),
		m_IsTracking(isTracking) {}

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
		m_EnemyList = m_Scene->GetGameObjects<Enemy>();

		if (m_EnemyList.empty())
		{
			m_IsNextWave = true;
		}
	}

	virtual void Draw() override {

	}

    virtual bool GetIsNextWave()const { return m_IsNextWave; }
    virtual EnemyWave* CreateNextWave() = 0;

    void SetStageFileName(const std::string& file) { m_StageFileName = file; }
};

