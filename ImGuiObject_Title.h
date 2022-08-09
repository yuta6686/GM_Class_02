#pragma once

#include "ImGuiObject.h"
#include "player.h"
#include "scene.h"
#include "manager.h"
#include "VertexChangerComponent_Color.h"
#include "CO_3DPloygonTest.h"
#include "CO_TitleBackGround.h"
#include "CO_ToriiBlock.h"
#include "CO_Confirmation.h"
#include "CO_UI_Quest.h"
#include "CO_UI_Quest_Purpose.h"
#include "CO_UI_Quest_Belt.h"

class ImGuiObject_Title :
	public ImGuiObject
{
	float ROTATION_MIN = -D3DX_PI;
	float ROTATION_MAX = D3DX_PI;
public:
	virtual void Draw()override
	{
		//	Rotation
		if (ImGui::CollapsingHeader("Player Rotation")) {

			D3DXVECTOR3 prot = m_Player->GetRotation();
			float frot[3] = { prot.x,prot.y,prot.z };

			ImGui::SliderFloat("Rotation X:",
				&frot[0], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Rotation Y:",
				&frot[1], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Rotation Z:",
				&frot[2], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			m_Player->SetRotation(frot);
		}

		if (ImGui::CollapsingHeader("VertexChange")) {
			std::shared_ptr<Scene> scene = Manager::GetScene();
			std::vector<CO_3DPloygonTest*> pol3d = scene->GetGameObjects<CO_3DPloygonTest>();
			for (auto pol : pol3d) {
				pol->GetComponent<VertexChangeComponent_ToGame>()->DrawImgui();
			}
			
			
		}
		
		if (ImGui::CollapsingHeader("CO_ToriiBlock")) {
			std::shared_ptr<Scene> scene = Manager::GetScene();
			CO_ToriiBlock* pol3d = scene->GetGameObject<CO_ToriiBlock>();
			pol3d->DrawImgui();

		}

		if (ImGui::CollapsingHeader("CO_Confirmation")) {
			std::shared_ptr<Scene> scene = Manager::GetScene();
			CO_Confirmation* con = scene->GetGameObject<CO_Confirmation>();

			if (con != nullptr) {
				con->DrawImgui();
			}			
		}

		if (ImGui::CollapsingHeader("CO_UI_Quest")) {
			std::shared_ptr<Scene> scene = Manager::GetScene();
			CO_UI_Quest* obj = scene->GetGameObject<CO_UI_Quest>();

			if (obj != nullptr) {
				obj->DrawImgui();
			}
		}

		if (ImGui::CollapsingHeader("CO_UI_Quest_Purpose")) {
			std::shared_ptr<Scene> scene = Manager::GetScene();
			CO_UI_Quest_Purpose* obj = scene->GetGameObject<CO_UI_Quest_Purpose>();

			if (obj != nullptr) {
				obj->DrawImgui();
			}
		}

		if (ImGui::CollapsingHeader("CO_UI_Quest_Belt")) {
			std::shared_ptr<Scene> scene = Manager::GetScene();
			CO_UI_Quest_Belt* obj = scene->GetGameObject<CO_UI_Quest_Belt>();

			if (obj != nullptr) {
				obj->DrawImgui();
			}
		}
	}
};

