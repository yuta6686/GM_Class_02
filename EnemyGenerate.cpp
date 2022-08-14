#include "EnemyGenerate.h"
#include "Enemy.h"
#include "Cylinder.h"

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void EnemyGenerate::Init()
{
	m_Scene = Manager::GetScene();
	for (int i = 1; i < 100;i++) {
		std::ostringstream oss;
		oss << i;
		ifstream ifs(m_FileName.c_str() + oss.str() + m_Version.c_str() + m_Extension.c_str());

		if (!ifs) {
			m_NowFileNum = i;
			break;
		}		
	}
	m_Player = m_Scene->GetGameObject<Player>();
}

void EnemyGenerate::Uninit()
{
}

void EnemyGenerate::Update()
{
#ifdef _DEBUG




	ImGui::PushStyleColor(ImGuiCol_WindowBg, window_color);

	ImGui::Begin("EnemyGenerate");
	

	ImGui::ColorEdit4("window color", (float*)&window_color);

	if (ImGui::Button("Generate!")) {
		m_Scene->AddGameObject<Enemy>(LAYER_3D)->SetMaxHp(10);	
	}
	ImGui::SameLine();
	if (ImGui::Button("Generate Player Transform") ||
		GetKeyboardTrigger(DIK_E)) {
		
		auto* enemy = m_Scene->AddGameObject<Enemy>(LAYER_3D);
		enemy->SetPosition(m_Player->GetPosition());
		//enemy->SetRotation(m_Player->GetRotation());
		enemy->SetMaxHp(1);
	}


	std::vector<GameObject*> enemys = m_Scene->GetGameObjectLayer(LAYER_ENEMY);


	ImGui::SliderInt("SaveFileIndex", &m_SaveFileIndex, 1, m_NowFileNum, "%d");
	
	ImGui::Separator();

	ImGui::SliderInt("LoadFileIndex", &m_LoadFileIndex, 1, m_NowFileNum-1, "%d");

	ImGui::Separator();

	

	if (ImGui::Button("Save_Enemy_Index_Version")) {
		if (m_SaveFileIndex == m_NowFileNum) {
			m_NowFileNum++;
		}

		std::ostringstream oss;

		oss << m_SaveFileIndex;

		//	FileName + FileIndex + Extension
		std::ofstream ofs(m_FileName.c_str() + oss.str() + m_Version.c_str() + m_Extension.c_str());

		if (!ofs) {
			ImGui::Text("Could not open file.");
		}

		for (int i = 0; i < enemys.size(); i++) {			

			ofs << showpoint
				<< enemys[i]->GetPosition().x << ","
				<< enemys[i]->GetPosition().y << ","
				<< enemys[i]->GetPosition().z << ","
				<< enemys[i]->GetRotation().x << ","
				<< enemys[i]->GetRotation().y << ","
				<< enemys[i]->GetRotation().z << ","
				<< enemys[i]->GetScale().x << ","
				<< enemys[i]->GetScale().y << ","
				<< enemys[i]->GetScale().z << ","
				<< dynamic_cast<Enemy_Interface*>(enemys[i])->GetMaxHp() << ","
				<< dynamic_cast<Enemy_Interface*>(enemys[i])->GetEnemyIndex() << std::endl;

		}
	}

	ImGui::Separator();

	if (ImGui::Button("Load_Enemy_Index_Version")) {

		std::ostringstream oss;

		oss << m_LoadFileIndex;

		ifstream ifs(m_FileName.c_str() + oss.str() + m_Version.c_str() + m_Extension.c_str());
		string str_buf;
		string str_conma_buf;
		vector<string> str_buf_vec;

		int index = 0;

		while (getline(ifs, str_buf)) {
			istringstream istream(str_buf);

			while (getline(istream, str_conma_buf, ',')) {
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

			Enemy_Interface* penemy;

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
			case ENEMY_MAX:
				penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
				break;
			default:
				penemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
				break;
			}			

			penemy->SetPosition(pos);
			penemy->SetRotation(rot);
			penemy->SetScale(sca);
			penemy->SetMaxHp(hp);
			penemy->SetHp(hp);	

			str_buf_vec.clear();
		}
	}

	if(ImGui::CollapsingHeader("Reset Enemy")) {
		if(ImGui::Button("Reset Enemy Button")) {
			for (auto enemy : enemys) {
				enemy->SetDestroy();
			}
		}
	}

	if (ImGui::CollapsingHeader("Velocity Allow")) {
		if (ImGui::Button("Enemy Velocity Is Not Add")) {
			for (auto enemy : enemys) {
				for (auto vel : enemy->GetComponents<VelocityComponent>()) {
					vel->SetNoAdd(true);
				}
			}
		}

		if (ImGui::Button("Enemy Velocity Is Add")) {
			for (auto enemy : enemys) {
				for (auto vel : enemy->GetComponents<VelocityComponent>()) {
					vel->SetNoAdd(false);
				}
			}
		}
	}


	//	Enemy
	if (ImGui::CollapsingHeader("Enemy")) {		
		for (int i = 0; i < enemys.size(); i++) {
			char buff[255];
			sprintf(buff, "Enemy_%d", i);
			if (ImGui::TreeNode(buff))
			{
				enemys[i]->DrawImgui();				
				ImGui::TreePop();
			}
			if (ImGui::Button("destroy")) {
				enemys[i]->SetDestroy();
			}
		}
	}

	ImGui::End();

	ImGui::PopStyleColor();

#endif // _DEBUG
}

void EnemyGenerate::Draw()
{

}

void EnemyGenerate::DrawImgui()
{
}
