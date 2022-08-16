#include "HPComponent.h"
#include "player.h"
#include "manager.h"
#include "CO_UI_PlayerHPGauge.h"

void HPComponent::Init()
{
	m_IsDeath = false;

	CO_UI_PlayerHPGauge* hpgauge = Manager::GetScene()->
		GetGameObject<CO_UI_PlayerHPGauge>();
	
	if (hpgauge) {
		m_UIComponent = hpgauge->
			GetComponent<UserInterfaceComponent>();

		m_UIComponent->SetLeftXPosition(LEFT_POSITION);
	}
	else
	{
		m_UIComponent = nullptr;
	}

}

void HPComponent::Uninit()
{
}

void HPComponent::Update()
{
	if (m_UIComponent == nullptr)return;

	float ratio = (float)m_Hp / (float)m_MaxHp;
	float result = 0.0f;
	MyMath::FloatLerp(&result,
		&LEFT_POSITION,
		&RIGHT_POSITION,
		ratio);

	m_UIComponent->SetRightXPosition(result);
	
	if (ratio <= 0.5f) {
		m_UIComponent->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	}

	if (ratio <= 0.2f) {
		m_UIComponent->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	}
}

void HPComponent::Draw()
{
	if (m_UIComponent == nullptr)return;
}

void HPComponent::DrawImgui()
{
	if (m_UIComponent == nullptr)return;
}
