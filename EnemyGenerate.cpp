#include "EnemyGenerate.h"
#include "Enemy.h"
#include "Cylinder.h"
#include "CircleDeploy.h"
#include "CollisionComponent_Player.h"

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void EnemyGenerate::SetEnemyGenerateMode(bool flag)
{
	if (!m_Player)return;
	if (flag) {
		m_Player->GetComponent<CollisionComponent_Player>()->SetIsGenerateMode(true);
		m_Player->SetIsUseBullet(true);
	}
	else {
		m_Player->GetComponent<CollisionComponent_Player>()->SetIsGenerateMode(false);
		m_Player->SetIsUseBullet(false);
	}
	
}

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

	
	ImGui::Checkbox("Set Enemy Generate Mode!", &IsEnemyGenerateMode);

	SetEnemyGenerateMode(IsEnemyGenerateMode);

	if (ImGui::CollapsingHeader("EnemyGenerate!")) {
		ImGui::SliderFloat("scale", &_scale, 0.0f, 30.0f,"%.2f");
		ImGui::SliderFloat("scale3.x", &_scale3.x, _scale, 30.0f);
		ImGui::SliderFloat("scale3.y", &_scale3.y, _scale, 30.0f);
		ImGui::SliderFloat("scale3.z", &_scale3.z, _scale, 30.0f);

		ImGui::SliderInt("hp", &_hp, 1, 3);
		ImGui::SliderInt("enemy_index", &_enemy_index, ENEMY_NORMAL, ENEMY_MAX);

		

		if(ImGui::TreeNode("ENEMY_INDEX")) {
			 ostringstream oss;
			oss << "0:ENEMY_NORMAL" << endl
				<< "1:ENEMY_TRACKING" << endl
				<< "2:ENEMY_TRACKING_FAST" << endl
				<< "3:ENEMY_TRACKING_LATE" << endl
				<< "4:ENEMY_NO_DRUM" << endl
				<< "5:ENEMY_MOVE_STRAIGHT" << endl
				<< "6:ENEMY_JUMP" << endl
				<< "7:ENEMY_BOSS" << endl;

			ImGui::Text(oss.str().c_str());
			ImGui::TreePop();
		}

		if (ImGui::Button("Generate!")) {
			m_Scene->AddGameObject<Enemy>(LAYER_ENEMY)->SetMaxHp(2);
		}

		ImGui::SameLine();

		if (ImGui::Button("Generate Player Transform") ||
			GetKeyboardTrigger(DIK_E)) {

			auto* enemy = m_Scene->AddGameObject<Enemy>(LAYER_ENEMY);
			enemy->SetPosition(m_Player->GetPosition());
			enemy->SetScale({ _scale3 });
			//enemy->SetRotation(m_Player->GetRotation());
			enemy->SetMaxHp(_hp);
		}

		if (ImGui::TreeNode("Enemy Circle Deploy")) {
			ImGui::SliderInt("NumLayer", &m_NumLayer, 1, m_NumLayer_Max);
			ImGui::SliderInt("NumLayer_Max", &m_NumLayer_Max, 1, 32);
			ImGui::SliderFloat("Radius", &m_Radius, 0.0f, 100.0f);
			ImGui::SliderFloat("Offset", &m_Offset, 0.0f, D3DX_PI);

			if (ImGui::Button("Deploy")) {
				CircleDeploy::AddGameObject_CircleDeploy<Enemy>
					(m_NumLayer, m_NumLayer_Max, m_Player->GetPosition(), m_Radius, m_Offset, LAYER_ENEMY);
			}

			ImGui::TreePop();
		}
	}


	std::vector<GameObject*> enemys = m_Scene->GetGameObjectLayer(LAYER_ENEMY);
	std::vector<Cylinder*> clies = m_Scene->GetGameObjects<Cylinder>();


	if (ImGui::CollapsingHeader("Save")) {

		ImGui::SliderInt("SaveFileIndex", &m_SaveFileIndex, 1, m_NowFileNum, "%d");

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

			//	エネミー
			for (unsigned int i = 0; i < enemys.size(); i++) {

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

			//	 シリンダー
			for (unsigned int i = 0; i < clies.size(); i++) {
				ofs << clies[i]->GetPosition().x << ","
					<< clies[i]->GetPosition().y << ","
					<< clies[i]->GetPosition().z << ","
					<< clies[i]->GetRotation().x << ","
					<< clies[i]->GetRotation().y << ","
					<< clies[i]->GetRotation().z << ","
					<< clies[i]->GetScale().x << ","
					<< clies[i]->GetScale().y << ","
					<< clies[i]->GetScale().z << ","
					<< 0 << ","
					<< ENEMY_NO_DRUM << std::endl;
			}
		}
	}
	

	if (ImGui::CollapsingHeader("Load")) {

		ImGui::SliderInt("LoadFileIndex", &m_LoadFileIndex, 1, m_NowFileNum - 1, "%d");

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

				Enemy_Interface* penemy = nullptr;
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

				if (penemy != nullptr) {
					penemy->SetPosition(pos);
					penemy->SetRotation(rot);
					penemy->SetScale(sca);
					penemy->SetMaxHp(hp);
					penemy->SetHp(hp);
				}

				str_buf_vec.clear();
			}
		}

		ImGui::SliderInt("StageNum:", &m_StageNum, 1, STAGE_NUM_MAX);
		ImGui::SliderInt("WaveNum:", &m_WaveNum, 1, WAVE_NUM_MAX);

		if (ImGui::Button("Load_Enemy_StageNum_WaveNum")) {

			std::ostringstream oss;

			oss << m_StageNum << "-" << m_WaveNum;

			ifstream ifs(m_FileName.c_str() + oss.str() + m_Extension.c_str());
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

				Enemy_Interface* penemy = nullptr;
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

				if (penemy != nullptr) {
					penemy->SetPosition(pos);
					penemy->SetRotation(rot);
					penemy->SetScale(sca);
					penemy->SetMaxHp(hp);
					penemy->SetHp(hp);
				}

				str_buf_vec.clear();
			}
		}
	}

	if(ImGui::CollapsingHeader("Reset")) {
		if(ImGui::Button("Reset Enemy Button")) {
			for (auto enemy : enemys) {
				enemy->SetDestroy();
			}
		}

		if (ImGui::Button("Reset Drum Button")) {
			for (auto cyl : m_Scene->GetGameObjects<Cylinder>()) {
				cyl->SetDestroy();
			}
		}
	}



	//	Enemy
	if (ImGui::CollapsingHeader("Enemy")) {		
		for (unsigned int i = 0; i < enemys.size(); i++) {
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

	std::vector<Cylinder*> cylinder = m_Scene->GetGameObjects< Cylinder>();
	if (ImGui::CollapsingHeader("Drum")) {
		for (unsigned int i = 0; i < cylinder.size(); i++) {
			std::ostringstream oss;
			oss << "Drum_" << i;
			if (ImGui::TreeNode(oss.str().c_str())) {
				cylinder[i]->DrawImgui();
				ImGui::TreePop();
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
