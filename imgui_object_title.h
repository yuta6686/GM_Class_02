#pragma once

#include "imgui_object.h"
#include "player.h"
#include "scene.h"

#include "vertex_changer_color_component.h"
#include "co_3dpolygon_test.h"
#include "co_title_background.h"
#include "co_torii_block.h"
#include "co_confirmation.h"
#include "co_ui_quest.h"
#include "co_ui_quest_purpose.h"
#include "co_ui_quest_belt.h"

class ImGuiObject_Title :
	public ImGuiObject
{
	float ROTATION_MIN = -D3DX_PI;
	float ROTATION_MAX = D3DX_PI;

	bool mMenu1 = false;
public:
	virtual void Draw()override
	{
#ifdef _DEBUG

		//	メニューバー
		// ImGui::BeginMenuBar();
		
		if (ImGui::BeginMenu("Enemy Generater")) 
		{
			if (ImGui::BeginMenu("Generate")) 
			{
				ImGui::Text("Set Parameter");
				ImGui::Button("Generate!");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Save"))
			{				
				ImGui::Text("Set Save Infomation");
				ImGui::Button("Save");
				ImGui::EndMenu();
			}
			
			if (ImGui::BeginMenu("Load")) 
			{
				ImGui::Text("Set Load Information");

				ImGui::Button("Load");

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		// ImGui::EndMenuBar();

		
		

		////	Rotation
		//if (ImGui::CollapsingHeader("Player Rotation")) {

		//	D3DXVECTOR3 prot = m_Player->GetRotation();
		//	float frot[3] = { prot.x,prot.y,prot.z };

		//	ImGui::SliderFloat("Rotation X:",
		//		&frot[0], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

		//	ImGui::SliderFloat("Rotation Y:",
		//		&frot[1], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

		//	ImGui::SliderFloat("Rotation Z:",
		//		&frot[2], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

		//	m_Player->SetRotation(frot);
		//}

		//if (ImGui::CollapsingHeader("VertexChange")) {
		//	std::shared_ptr<Scene> scene = Manager::GetScene();
		//	std::vector<CO_3DPloygonTest*> pol3d = scene->GetGameObjects<CO_3DPloygonTest>();
		//	for (auto pol : pol3d) {
		//		if (pol == nullptr)continue;
		//		pol->GetComponent<VertexChangeComponent_ToGame>()->DrawImgui();
		//	}
		//	
		//	
		//}
		//
		//if (ImGui::CollapsingHeader("CO_ToriiBlock")) {
		//	std::shared_ptr<Scene> scene = Manager::GetScene();
		//	CO_ToriiBlock* pol3d = scene->GetGameObject<CO_ToriiBlock>();
		//	if (pol3d) {
		//		pol3d->DrawImgui();
		//	}
		//	

		//}

		//if (ImGui::CollapsingHeader("CO_Confirmation")) {
		//	std::shared_ptr<Scene> scene = Manager::GetScene();
		//	CO_Confirmation* con = scene->GetGameObject<CO_Confirmation>();

		//	if (con != nullptr) {
		//		con->DrawImgui();
		//	}			
		//}

		//if (ImGui::CollapsingHeader("CO_UI_Quest")) {
		//	std::shared_ptr<Scene> scene = Manager::GetScene();
		//	CO_UI_Quest* obj = scene->GetGameObject<CO_UI_Quest>();

		//	if (obj != nullptr) {
		//		obj->DrawImgui();
		//	}
		//}

		//if (ImGui::CollapsingHeader("CO_UI_Quest_Purpose")) {
		//	std::shared_ptr<Scene> scene = Manager::GetScene();
		//	CO_UI_Quest_Purpose* obj = scene->GetGameObject<CO_UI_Quest_Purpose>();

		//	if (obj != nullptr) {
		//		obj->DrawImgui();
		//	}
		//}

		//if (ImGui::CollapsingHeader("CO_UI_Quest_Belt")) {
		//	std::shared_ptr<Scene> scene = Manager::GetScene();
		//	CO_UI_Quest_Belt* obj = scene->GetGameObject<CO_UI_Quest_Belt>();

		//	if (obj != nullptr) {
		//		obj->DrawImgui();
		//	}
		//}

#endif // _DEBUG
	}
};

