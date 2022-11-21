#include "player_factory.h"

#include "player.h"

#include "co_ui_player_hp_gauge.h"
#include "co_ui_dot.h"
#include "co_ui_line.h"

void PlayerFactory::CreateUI()
{
	//	プレイヤーの前に入れる
	_scene->AddGameObject<CO_UI_dot>(LAYER_2D);
	_scene->AddGameObject< CO_UI_PlayerHPGauge>(LAYER_2D);
	_scene->AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,55.0f,0.0f });
	_scene->AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,85.0f,0.0f });
}

void PlayerFactory::Create()
{	
	CreateUI();
	
	// プレイヤー
	auto player = _scene->AddGameObject<Player>(LAYER_3D);
	player->SetPosition({ 2.5f,5.0f,0.0f });
}
