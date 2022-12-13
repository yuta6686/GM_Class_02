#include "stdafx.h"
#include "hp_component.h"
#include "user_interface_component.h"
#include "player.h"

#include "co_ui_player_hp_gauge.h"

HPComponent::HPComponent()
	:_hp(10),
	_maxHp(10),
	_isDeath(false),
	_uiComponent(nullptr)
{
}

void HPComponent::Init()
{
	_isDeath = false;

	CO_UI_PlayerHPGauge* hpgauge = Manager::GetScene()->
		GetGameObject<CO_UI_PlayerHPGauge>();
	
	if (hpgauge) {
		_uiComponent = hpgauge->
			GetComponent<UserInterfaceComponent>();

		_uiComponent->SetLeftXPosition(LEFT_POSITION);
	}
	else
	{
		_uiComponent = nullptr;
	}

}

void HPComponent::Uninit()
{
}

void HPComponent::Update()
{
	if (_uiComponent == nullptr)return;

	float ratio = (float)_hp / (float)_maxHp;
	float result = 0.0f;
	float start = 0.0f;
	MyMath::FloatLerp(&result,
		&start,
		&RIGHT_POSITION,
		ratio);

	_uiComponent->SetRightXPosition(result);
	
	if (ratio <= 0.5f) {
		_uiComponent->SetColor({ 1.0f,1.0f,0.0f,1.0f });
	}

	if (ratio <= 0.2f) {
		_uiComponent->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	}
}

void HPComponent::Draw()
{
	if (_uiComponent == nullptr)return;
}

void HPComponent::DrawImgui()
{
	if (_uiComponent == nullptr)return;

	ImGui::Text("HPRatio : %.2f", (float)_hp / (float)_maxHp);
}



void HPComponent::RecoverHp(const int& hp)
{
	_hp += hp;
	if (_hp > _maxHp)
	{
		_hp = _maxHp;
	}
}
void HPComponent::ResetHp()
{
	_hp = _maxHp;
}
void HPComponent::SetMaxHp(const int& maxHp)
{
	_maxHp = maxHp;
}
void HPComponent::TakeDamage(const int& damage)
{
	_hp -= damage;

	if (_hp <= 0) {
		_isDeath = true;
	}
}
