#include "ImGuiComponent.h"
#include "gameObject.h"
#include "ComponentObject.h"


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
#ifdef _DEBUG


	ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(400, 500));

	//	Position
	{
		D3DXVECTOR3 ppos = m_Parent->GetPosition();
		float fpos[3] = { ppos.x,ppos.y,ppos.z };

		ImGui::SliderFloat("Position X:",
			&fpos[0], POSITION_MIN, POSITION_MAX, "%.3f", 1.0f);

		ImGui::SliderFloat("Position Y:",
			&fpos[1], POSITION_MIN, POSITION_MAX, "%.3f", 1.0f);

		ImGui::SliderFloat("Position Z:",
			&fpos[2], POSITION_MIN, POSITION_MAX, "%.3f", 1.0f);



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

	ImGui::EndChild();


#endif // _DEBUG
}
