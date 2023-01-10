#include "stdafx.h"
#include "ModelColorChangeComponent_Titlebg.h"
#include "model_draw_component.h"
#include "co_3dpolygon_test.h"

void ModelColorChangeComponent_Titlebg::Init()
{
	m_Scene = Manager::GetScene();
	m_poly3d = m_Scene->GetGameObjects<CO_3DPloygonTest>();

}
 void ModelColorChangeComponent_Titlebg::Update()  {

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