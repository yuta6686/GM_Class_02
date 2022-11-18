#include "blink_component.h"
#include "gameObject.h"

void BlinkComponent::Update()
{
	m_Work += m_Speed;

	if (m_Work > D3DX_PI * 2.0f) {
		m_Work = 0.0f;
	}

	m_BlinkValue = (sinf(m_Work) + 1.0f) / (2.0f) * (m_Max - m_Min) + m_Min;	
}

void BlinkComponent::DrawImgui()
{
	ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 1.0f);
	ImGui::SliderFloat("AlphaMin", &m_Min, -1.0f, 1.0f);
	ImGui::SliderFloat("AlphaMax", &m_Max, -1.0f, 1.0f);
	ImGui::SliderFloat("Alpha", &m_BlinkValue, m_Min, m_Max);
}
