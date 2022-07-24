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
	ImGui::Begin(m_Parent->GetTypeName().c_str());
	{
		//	Position
		{
			D3DXVECTOR3 ppos = m_Parent->GetPosition();
			float fpos[3] = { ppos.x,ppos.y,ppos.z };

			ImGui::SliderFloat3("Position",
				fpos, POSITION_MIN, POSITION_MAX, "%.3f", 1.0f);

			m_Parent->SetPosition(fpos);
		}

		//	Rotation
		{
			D3DXVECTOR3 prot = m_Parent->GetRotation();
			float frot[3] = { prot.x,prot.y,prot.z };

			ImGui::SliderFloat3("Rotation",
				frot, ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			m_Parent->SetRotation(frot);
		}

		//	Scale
		{
			D3DXVECTOR3 psca = m_Parent->GetScale();
			float fsca[3] = { psca.x,psca.y,psca.z };

			ImGui::SliderFloat3("Scale",
				fsca, SCALE_MIN, SCALE_MAX, "%.3f", 1.0f);

			m_Parent->SetScale(fsca);
		}
	}
	ImGui::End();
#endif // _DEBUG
}
