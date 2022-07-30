#include "ImGuiObject.h"
#include "manager.h"
#include "GameScene.h"
#include "player.h"	
#include "Enemy.h"
#include "Bullet.h"
#include "CO_UI_AimLing.h"
#include "BlinkComponentAlpha2D.h"
#include "Enemy.h"

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

	if (ImGui::CollapsingHeader("CO_UI_test")) {
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<ImGuiComponent>()->DrawImgui();
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<UserInterfaceComponent>()->DrawImgui();
	}



	if (ImGui::CollapsingHeader("AlphaBlink2DComponent")) {		
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<AlphaBlink2DComponent>()->DrawImgui();
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<Rotate2D>()->DrawImgui();
	}

	//Enemy
	if (ImGui::CollapsingHeader("Enemy"))
	{
		std::vector<Enemy*> enemy = m_Scene->GetGameObjects<Enemy>();
		for (int i = 0; i < enemy.size(); i++)
		{
			char buff[255];
			sprintf(buff, "Enemy_%d", i);
			if (ImGui::TreeNode(buff))
			{
				enemy[i]->DrawImgui();
				ImGui::TreePop();
			}
		}
	}

#endif // _DEBUG
}
