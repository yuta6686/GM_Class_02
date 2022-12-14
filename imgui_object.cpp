//  ---------------------------------------------------------
//  ImGuiObject [ImGuiObject.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  -ImGui‚Ì“Š‡ˆ—
//  ---------------------------------------------------------
#include "imgui_object.h"

#include "game_scene.h"
#include "player.h"	
#include "enemy.h"
#include "bullet.h"
#include "co_ui_aimling.h"
#include "blink_alpha2d_component.h"
#include "audio.h"
#include "component_object_test.h"
#include "model_color_change_component.h"
#include "co_ui_quest.h"
#include "co_enemy_wave.h"
#include "co_ui_tutorial_move.h"
#include "rotate2d_component.h"

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

	//	Bullet
	if (MyImgui::_myFlag["Bullet"] && ImGui::CollapsingHeader("Bullet")) {
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

	if (MyImgui::_myFlag["Audio"] &&ImGui::CollapsingHeader("Audio")) {
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

	if (MyImgui::_myFlag["CO_UI_test"] && ImGui::CollapsingHeader("CO_UI_test")) {
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<ImGuiComponent>()->DrawImgui();
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<UserInterfaceComponent>()->DrawImgui();
	}



	if (MyImgui::_myFlag["AlphaBlink2DComponent"] && ImGui::CollapsingHeader("AlphaBlink2DComponent")) {
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<AlphaBlink2DComponent>()->DrawImgui();
		m_Scene->GetGameObject<CO_UI_AimLing>()->GetComponent<Rotate2D>()->DrawImgui();
	}

	if(MyImgui::_myFlag["CO_UI_Quest"] && ImGui::CollapsingHeader("CO_UI_Quest")) {
		m_Scene->GetGameObject<CO_UI_Quest>()->DrawImgui();
	}

	if (MyImgui::_myFlag["CO_EnemyWave"] && ImGui::CollapsingHeader("CO_EnemyWave")) {
		m_Scene->GetGameObject< CO_EnemyWave>()->DrawImgui();
	}

	//Enemy
	if (MyImgui::_myFlag["Enemy"] && ImGui::CollapsingHeader("Enemy"))
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
	if (MyImgui::_myFlag["ComponentObjectTest"] && ImGui::CollapsingHeader("ComponentObjectTest"))
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

	if (MyImgui::_myFlag["Tutorial UI"] && ImGui::CollapsingHeader("Tutorial UI")) {
		std::vector<CO_UI_Tutorial*> cot = m_Scene->GetGameObjects<CO_UI_Tutorial>();
		for (unsigned int i = 0; i < cot.size(); i++)
		{			
			if (ImGui::TreeNode(cot[i]->m_Name.c_str()))
			{
				cot[i]->DrawImgui();				
				ImGui::TreePop();
			}
		}		
	}
	if (MyImgui::_myFlag["Monochrome"] && ImGui::CollapsingHeader("Monochrome")) {
		ImGui::SliderFloat("MonochromeRate:", &MyMath::m_MonochromeRate.MonochoromeRate, 0.0f, 1.0f, "%.2f");
		Renderer::SetValiable(MyMath::m_MonochromeRate);
	}


	if (MyImgui::_myFlag["hello"] && ImGui::CollapsingHeader("hello")) {


		ImGui::Checkbox("showDemoWindow", &MyImgui::_myFlag["showDemoWindow"]);
		

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)			

			std::shared_ptr<Scene> scene = Manager::GetScene();
			ImGui::Checkbox("Parameters by scene", &scene->parameters_by_scene);

			
			ImGui::ColorEdit4("window color", (float*)&MyImgui::window_color);


			ImGui::SetNextWindowSize(ImVec2(MyImgui::window_color.x, MyImgui::window_color.y));

			
			ImGui::Text("Framerate : %.1f FPS", ImGui::GetIO().Framerate);
			ImGui::SameLine();
			ImGui::ProgressBar(ImGui::GetIO().Framerate / 60.0f);

			ImGui::Text("MousePosDiffX: %d \nMousePosDiffY: %d", GetMouseX(), GetMouseY());

			ImGui::Text("Mouse_X: %.f", ImGui::GetIO().MousePos.x);
			ImGui::SameLine();
			ImGui::ProgressBar(ImGui::GetIO().MousePos.x / SCREEN_WIDTH);

			ImGui::Text("Mouse_Y: %.f", ImGui::GetIO().MousePos.y);
			ImGui::SameLine();
			ImGui::ProgressBar(ImGui::GetIO().MousePos.y / SCREEN_HEIGHT);


		}
	}

#endif // _DEBUG
}
