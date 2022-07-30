#include "Rotate2D.h"
#include "gameObject.h"

void Rotate2D::Init()
{
}

void Rotate2D::Uninit()
{
}

void Rotate2D::Update()
{		
	D3DXVECTOR3 pos = m_Parent->GetPosition();

	float nsin = sinf(MyMath::GetRadian(m_Angle));
	float ncos = cosf(MyMath::GetRadian(m_Angle));		

	pos.x -= m_CenterPosition.x;
	pos.y -= m_CenterPosition.y;

	float nx = ncos * pos.x - nsin * pos.y;
	float ny = nsin * pos.x + ncos * pos.y;
	
	pos.x = nx + m_CenterPosition.x;
	pos.y = ny + m_CenterPosition.y;

	m_Parent->SetPosition(pos);		
}

void Rotate2D::Draw()
{
}

void Rotate2D::DrawImgui()
{
	ImGui::SliderFloat("m_Angle", &m_Angle, -5.0f, 5.0f, "%.3f");
	ImGui::SliderFloat("CenterPosition.x", &m_CenterPosition.x, 0.0f, SCREEN_WIDTH, "%.2f");
	ImGui::SliderFloat("CenterPosition.y", &m_CenterPosition.y, 0.0f, SCREEN_HEIGHT, "%.2f");
}
