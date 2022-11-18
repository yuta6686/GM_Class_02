//  ---------------------------------------------------------
//  ImGuiComponent [ImGuiComponent.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - Transform•\Ž¦E’²®
//  ---------------------------------------------------------
#include "imgui_component.h"
#include "gameObject.h"
#include "component_object.h"
#include "enemy.h"
#include "my_imgui.h"

#define nameof(x) #x

void ImGuiComponent::Init()
{
}

void ImGuiComponent::Uninit()
{
}

void ImGuiComponent::Update()
{
}

void ImGuiComponent::Draw()
{

}

void ImGuiComponent::DrawImgui()
{
#ifdef _DEBUG

	//ImGui::BeginChild(ImGui::GetID((void*)0),
	//	ImVec2(SCREEN_WIDTH,SCREEN_HEIGHT/2.0f));	
	
	if (ImGui::CollapsingHeader(m_Parent->GetTypeName().c_str())) {

		//	Position
		{
			D3DXVECTOR3 ppos = m_Parent->GetPosition();
			float fpos[3] = { ppos.x,ppos.y,ppos.z };

			if (m_Is2D) {
				int a = 0;
				ImGui::SliderInt("a", &a, 0, 1000, "%d", ImGuiSliderFlags_AlwaysClamp);

				ImGui::SliderFloat("Position X:",
					&fpos[0], POSITION_MIN_2D, POSITION_MAX_X_2D, "%.3f", 1.0f);

				ImGui::SliderFloat("Position Y:",
					&fpos[1], POSITION_MIN_2D, POSITION_MAX_Y_2D, "%.3f", 1.0f);

				ImGui::SliderFloat("Position Z:",
					&fpos[2], POSITION_MIN_2D, POSITION_MIN_2D, "%.3f", 1.0f);
			}
			else {
				ImGui::SliderFloat("Position X:",
					&fpos[0], POSITION_MIN, POSITION_MAX, "%.3f", 1.0f);

				ImGui::SliderFloat("Position Y:",
					&fpos[1], POSITION_MIN, POSITION_MAX, "%.3f", 1.0f);

				ImGui::SliderFloat("Position Z:",
					&fpos[2], POSITION_MIN, POSITION_MAX, "%.3f", 1.0f);
			}





			m_Parent->SetPosition(fpos);
		}

		//	Rotation
		{
			D3DXVECTOR3 prot = m_Parent->GetRotation();
			float frot[3] = { prot.x,prot.y,prot.z };

			ImGui::SliderFloat("Rotation X:",
				&frot[0], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Rotation Y:",
				&frot[1], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Rotation Z:",
				&frot[2], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			m_Parent->SetRotation(frot);
		}

		//	Scale
		{
			D3DXVECTOR3 psca = m_Parent->GetScale();
			float fsca[3] = { psca.x,psca.y,psca.z };

			ImGui::SliderFloat("Scale X:",
				&fsca[0], SCALE_MIN, SCALE_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Scale Y:",
				&fsca[1], SCALE_MIN, SCALE_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Scale Z:",
				&fsca[2], SCALE_MIN, SCALE_MAX, "%.3f", 1.0f);

			m_Parent->SetScale(fsca);
		}

		//	Length
		{
			ImGui::Text("Length %.2f", m_Parent->GetLength());
		}

		if (m_IsEnemyVersion) {
			auto pEnemy = dynamic_cast<Enemy*>(m_Parent);

			if (pEnemy != nullptr) {

				int hp = pEnemy->GetMaxHp();

				ImGui::Text("HP     : %d", pEnemy->GetHp());
				ImGui::Text("Max Hp : %d", hp);
				ImGui::ProgressBar(static_cast<float>(pEnemy->GetHp()) / static_cast<float>(hp));
				ImGui::SliderInt("Enemy Max HP", &hp, 1, 100, "%d");

				pEnemy->SetMaxHp(hp);
			}
		}
	}

	//ImGui::EndChild();


#endif // _DEBUG
}

