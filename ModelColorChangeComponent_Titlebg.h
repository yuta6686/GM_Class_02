#pragma once
#include "model_color_change_component.h"
#include "model_draw_component.h"
#include "scene.h"
#include "manager.h"
#include "CO_3DPloygonTest.h"

class ModelColorChangeComponent_Titlebg :
    public ModelColorChangeComponent
{
private:
	std::shared_ptr<Scene> m_Scene;
	std::vector<CO_3DPloygonTest*> m_poly3d;
public:
	virtual void Init()override
	{
		m_Scene = Manager::GetScene();
		m_poly3d = m_Scene->GetGameObjects<CO_3DPloygonTest>();
		
	}
    virtual void Update() override {

		for (auto pol : m_poly3d) {
		    VertexChangeComponent_ToGame* vcct = pol->GetComponent<VertexChangeComponent_ToGame>();

			if (vcct->GetIsToGameAndInside())
			{
				m_Diffuse = (D3DXCOLOR)vcct->GetToGameColor();
				break;
			}
			else if (vcct->GetIsToExitAndInside())
			{
				m_Diffuse = (D3DXCOLOR)vcct->GetToExitColor();
				break;
			}
			else
			{
				m_Diffuse = (D3DXCOLOR)vcct->GetFrontFaceColor();
			}

		}
		m_Parent->GetComponent<ModelDrawComponent>()->SetDiffuse(m_Diffuse);
			
    }
	
};

