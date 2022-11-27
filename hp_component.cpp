#include "stdafx.h"
#include "hp_component.h"
#include "user_interface_component.h"
#include "player.h"

#include "co_ui_player_hp_gauge.h"

HPComponent::HPComponent()
	:m_Hp(10),
	m_MaxHp(10),
	m_IsDeath(false),
	m_UIComponent(nullptr)
{
}

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
	float start = 0.0f;
	MyMath::FloatLerp(&result,
		&start,
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

	ImGui::Text("HPRatio : %.2f", (float)m_Hp / (float)m_MaxHp);
}



void HPComponent::RecoverHp(const int& hp)
{
	m_Hp += hp;
	if (m_Hp > m_MaxHp)
	{
		m_Hp = m_MaxHp;
	}
}
void HPComponent::ResetHp()
{
	m_Hp = m_MaxHp;
}
void HPComponent::SetMaxHp(const int& maxHp)
{
	m_MaxHp = maxHp;
}
void HPComponent::TakeDamage(const int& damage)
{
	m_Hp -= damage;

	if (m_Hp <= 0) {
		m_IsDeath = true;
	}
}
