#include "StageLimitDeleteComponent.h"
#include "gameObject.h"

void StageLimitDeleteComponent::Init()
{
}

void StageLimitDeleteComponent::Uninit()
{
}

void StageLimitDeleteComponent::Update()
{
	//	ŒÀŠE’l
	D3DXVECTOR3 ppos = m_Parent->GetPosition();
	if (ppos.z > Z_MAX ||
		ppos.z < Z_MIN ||
		ppos.x > X_MAX ||
		ppos.x < X_MIN || 
		ppos.y > Y_MAX ||
		ppos.y < Y_MIN)
	{
		m_Parent->SetDestroy();
		return;
	}
}

void StageLimitDeleteComponent::Draw()
{
}

void StageLimitDeleteComponent::DrawImgui()
{
	if(m_NoLimit)
		ImGui::Text("No Limit Value");
}
