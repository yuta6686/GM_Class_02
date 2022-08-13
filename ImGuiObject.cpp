#include "ImGuiObject.h"
#include "manager.h"
#include "GameScene.h"
#include "player.h"	
#include "Enemy.h"
#include "Bullet.h"
#include "CO_UI_AimLing.h"
#include "BlinkComponentAlpha2D.h"
#include "Enemy.h"
#include "audio.h"
#include "ComponentObjectTest.h"
#include "ModelColorChangeComponent.h"
#include "CO_UI_Quest.h"
#include "CO_EnemyWave.h"

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
		for (unsigned int i = 0; i < bullets.size(); i++) {
			char buff[255];
			sprintf(buff, "Bullet_%d", i);
			if (ImGui::TreeNode(buff))
			{
				bullets[i]->DrawImgui();
				ImGui::TreePop();
			}
		}
	}

	if (ImGui::CollapsingHeader("Audio")) {
		std::vector<Audio*> audios = m_Scene->GetGameObjects<Audio>();
		for (unsigned int i = 0; i < audios.size(); i++) {
			char buff[255];
			sprintf(buff, "Audio_%d", i);
			if (ImGui::TreeNode(buff))
			{
				audios[i]->DrawImgui();
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

	if(ImGui::CollapsingHeader("CO_UI_Quest")) {
		m_Scene->GetGameObject<CO_UI_Quest>()->DrawImgui();
	}

	if (ImGui::CollapsingHeader("CO_EnemyWave")) {
		m_Scene->GetGameObject< CO_EnemyWave>()->DrawImgui();
	}

	//Enemy
	if (ImGui::CollapsingHeader("Enemy"))
	{
		std::vector<Enemy*> enemy = m_Scene->GetGameObjects<Enemy>();
		for (unsigned int i = 0; i < enemy.size(); i++)
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

	//ComponentObjectTest
	if (ImGui::CollapsingHeader("ComponentObjectTest"))
	{
		std::vector<ComponentObjectTest*> cot = m_Scene->GetGameObjects<ComponentObjectTest>();
		for (unsigned int i = 0; i < cot.size(); i++)
		{
			char buff[255];
			sprintf(buff, "ComponentObjectTest_%d", i);
			if (ImGui::TreeNode(buff))
			{
				cot[i]->DrawImgui();	
				cot[i]->GetComponent<ModelColorChangeComponent>()->DrawImgui();
				ImGui::TreePop();
			}
		}
	}

	ImGui::SliderFloat("MonochromeRate:", &MyMath::m_MonochromeRate.MonochoromeRate, 0.0f, 1.0f, "%.2f");		
	Renderer::SetValiable(MyMath::m_MonochromeRate);

#endif // _DEBUG
}
