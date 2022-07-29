#include "ImGuiObject.h"
#include "manager.h"
#include "GameScene.h"
#include "player.h"	
#include "Enemy.h"
#include "Bullet.h"


void ImGuiObject::Init()
{
	m_PlayerWindow = true;

	m_Scene = Manager::GetScene();
	m_Player = m_Scene->GetGameObject<Player>();
}

void ImGuiObject::Uninit()
{
}

void ImGuiObject::Update()
{
}

void ImGuiObject::Draw()
{
#ifdef _DEBUG
	
	//	Player
	if (ImGui::CollapsingHeader("Player")) {
		m_Player->DrawImgui();
	}


	//	Enemy
	if (ImGui::CollapsingHeader("Enemy")) {
		std::vector<Enemy*> enemys = m_Scene->GetGameObjects<Enemy>();
		for (int i = 0; i < enemys.size();i++) {
			char buff[255];
			sprintf(buff, "Enemy_%d", i);
			if (ImGui::TreeNode(buff)) 
			{
				enemys[i]->DrawImgui();
				ImGui::TreePop();
			}
		}
	}
	
	//	Bullet
	if (ImGui::CollapsingHeader("Bullet")) {
		std::vector<Bullet*> bullets = m_Scene->GetGameObjects<Bullet>();
		for (int i = 0; i < bullets.size(); i++) {
			char buff[255];
			sprintf(buff, "Bullet_%d", i);
			if (ImGui::TreeNode(buff))
			{
				bullets[i]->DrawImgui();
				ImGui::TreePop();
			}
		}
	}
	
#endif // _DEBUG
}
