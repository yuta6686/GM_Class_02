#include "ui_factory.h"

#include "co_ui_aimling.h"
#include "co_ui_quest.h"
#include "co_ui_quest_purpose.h"
#include "co_ui_quest_belt.h"
#include "co_ui_tutorial_move.h"

#include "particle_object_2d.h"

void UIFactory::Create()
{
}

void UIGameSceneFactory::Create()
{
	// パーティクルなかったら作成
	if (_scene->GetGameObject<ParticleObject_2D>() == nullptr)
		_scene->AddGameObject<ParticleObject_2D>(LAYER_2D);

	//	User Interface
	_scene->AddGameObject<CO_UI_AimLing>(LAYER_2D);	
	_scene->AddGameObject<CO_UI_Quest>(LAYER_2D);
	_scene->AddGameObject< CO_UI_Quest_Purpose>(LAYER_2D);

	float dest_y = 400.0f;
	float dep_y = 800.0f;
	{
		CO_UI_Quest_Belt* couibelt = _scene->AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
		couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y,0.0f });
		couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y,0.0f });
		couibelt->Start(false, 60, 60);
	}

	{
		float sep_y = 200.0f;
		CO_UI_Quest_Belt* couibelt = _scene->AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
		couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y + sep_y,0.0f });
		couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y + sep_y,0.0f });
		couibelt->Start(false, 60, 90);
	}

	_scene->AddGameObject< CO_UI_Tutorial_Move>(LAYER_2D);
}
