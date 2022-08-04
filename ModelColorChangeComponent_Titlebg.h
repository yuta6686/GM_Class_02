#pragma once
#include "ModelColorChangeComponent.h"
#include "ModelDrawComponent.h"
#include "scene.h"
#include "manager.h"
#include "CO_3DPloygonTest.h"

class ModelColorChangeComponent_Titlebg :
    public ModelColorChangeComponent
{
private:
	std::shared_ptr<Scene> m_Scene;
	CO_3DPloygonTest* m_poly3d;
public:
	virtual void Init()override
	{
		m_Scene = Manager::GetScene();
		m_poly3d = m_Scene->GetGameObject<CO_3DPloygonTest>();
	}
    virtual void Update() override {

		VertexChangeComponent_ToGame* vcct = m_poly3d->GetComponent<VertexChangeComponent_ToGame>();

		if (vcct->GetIsToGame())
		{
			m_Diffuse = (D3DXCOLOR)vcct->GetToGameColor();
		}
		else if (vcct->GetIsToExit()) 
		{
			m_Diffuse = (D3DXCOLOR)vcct->GetToExitColor();
		}
		else 
		{
			m_Diffuse = (D3DXCOLOR)vcct->GetFrontFaceColor();
		}

		ImGui::Begin("ModelColorchange_Title");


		static ImGuiComboFlags flag = vcct->GetIsToExit();
		
		ImGui::CheckboxFlags("ToExit", &flag, ImGuiComboFlags_PopupAlignLeft);

		ImVec4 color;
		color.x = m_Diffuse.r;
		color.y = m_Diffuse.g;
		color.z = m_Diffuse.b;
		color.w = m_Diffuse.a;

		ImGui::ColorEdit4("diffuse", (float*)&color);

		m_Diffuse.r = color.x;
		m_Diffuse.g = color.y;
		m_Diffuse.b = color.z;
		m_Diffuse.a = color.w;

		ImGui::End();

		m_Parent->GetComponent<ModelDrawComponent>()->SetDiffuse(m_Diffuse);
    }

};

