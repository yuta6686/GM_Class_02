#include "EnemyGenerate.h"
#include "Enemy.h"

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
		ifstream ifs(m_FileName.c_str() + oss.str() + m_Extension.c_str());

		if (!ifs) {
			m_NowFileNum = i;
			break;
		}		
	}
}

void EnemyGenerate::Uninit()
{
}

void EnemyGenerate::Update()
{
	ImGui::Begin("EnemyGenerate");

	if (ImGui::Button("Generate!")) {
		m_Scene->AddGameObject<Enemy>(LAYER_3D)->SetMaxHp(10);
	}

	std::vector<Enemy*> enemys = m_Scene->GetGameObjects<Enemy>();

	

	if (ImGui::Button("Save!")) {
		m_NowFileNum++;
		std::ostringstream oss;

		oss << m_SaveFileIndex;		
		
		//	FileName + FileIndex + Extension
		std::ofstream ofs(m_FileName.c_str() + oss.str() + m_Extension.c_str());

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
				<< enemys[i]->GetScale().z  << std::endl;

		}
	}

	ImGui::SliderInt("SaveFileIndex", &m_SaveFileIndex, 1, m_NowFileNum, "%d");
	
	ImGui::Separator();

	if (ImGui::Button("Load")) {
				
		std::ostringstream oss;

		oss << m_LoadFileIndex;

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

			pos.x = stof(str_buf_vec[0]);
			pos.y = stof(str_buf_vec[1]);
			pos.z = stof(str_buf_vec[2]);

			rot.x = stof(str_buf_vec[3]);
			rot.y = stof(str_buf_vec[4]);
			rot.z = stof(str_buf_vec[5]);
			
			sca.x = stof(str_buf_vec[6]);
			sca.y = stof(str_buf_vec[7]);
			sca.z = stof(str_buf_vec[8]);

			auto* penemy = m_Scene->AddGameObject<Enemy>(LAYER_3D);

			penemy->SetPosition(pos);
			penemy->SetRotation(rot);
			penemy->SetScale(sca);
			

			str_buf_vec.clear();
		}

	}
	ImGui::SliderInt("LoadFileIndex", &m_LoadFileIndex, 1, m_NowFileNum-1, "%d");


	if(ImGui::CollapsingHeader("Reset Enemy")) {
		if(ImGui::Button("Reset Enemy Button")) {
			for (auto enemy : enemys) {
				enemy->SetDestroy();
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
		}
	}

	ImGui::End();
}

void EnemyGenerate::Draw()
{

}

void EnemyGenerate::DrawImgui()
{
}
