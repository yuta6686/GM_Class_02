#include "ResultScene.h"
#include "ResultPolygon.h"
#include "manager.h"
#include "TitleScene.h"
#include "Transition.h"
#include "CO_UI_Select.h"
#include "CO_Select.h"
#include "ExitScene.h"
#include "GameScene.h"
#include "CO_UI_Default.h"
#include "ParticleObject_2D.h"

void ResultScene::Init()
{
	AddGameObject<ResultPolygon>(LAYER_2D);


	for (int i = 0; i < 3; i++) {
		AddGameObject<CO_UI_Select>(LAYER_2D)
			->SetTrue_False_Position({ SCREEN_WIDTH / 2.0f,700.0f + 70.0f * i,0.0f }, 0.0f);
	}
	for (int i = 0; i < 3; i++) {
		CO_UI_Select* select = AddGameObject<CO_UI_Select>(LAYER_2D);
		select->SetTrue_False_Position({ SCREEN_WIDTH / 2.0f + 100.0f,700.0f + 70.0f * i,0.0f }, 10.0f);
		select->SetIsString();
		select->GetComponent<UserInterfaceComponent>()->
			LoadTexture(CO_UI_Select::GetFileName_Box()[i]);
	}

	//	CO_UI_Selectのあとにやる
	m_Select = AddGameObject< CO_Select>(LAYER_2D);
	m_Select->SetBlue(true);

	m_NextIsExit = false;
	m_NextIsGame = false;
	m_NextIsTitle = false;
	m_ChangeScene = false;

	UI_Information uii;
	uii._deploy_index = DEPLOY_CENTER;
	uii._texture = "asset\\texture\\GameClear.png";
	uii._main_pos = { 200.0f ,50.0f,0.0f };

	AddGameObject< CO_UI_Default>(LAYER_2D)->SetUIInfo(uii, { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f - 100.0f,0.0f });

	m_Particle = AddGameObject<ParticleObject_2D>(LAYER_2D);

	Renderer::SetValiable({ 0.0f,1.0f,1.0f,1.0f });

	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);
}

void ResultScene::Update()
{
	m_Particle->SetParticle_Rising();


	Scene::Update();

	switch (m_Select->GetSelect())
	{

	case SELECT_GIVE_UP:
		//	Exit
		m_NextIsExit = true;
		m_ChangeScene = true;
		break;
	case SELECT_CONTINUE:
		//	GameScene
		m_NextIsGame = true;
		m_ChangeScene = true;
		break;
	case SELECT_RETURN_TO_TITLE:
		//	Title
		m_NextIsTitle = true;
		m_ChangeScene = true;
		break;
	default:
		//	何もしない
		m_ChangeScene = false;
		break;
	}

	if (m_ChangeScene) {
		m_ChangeScene = false;
		m_Fade->Start(false);
	}

	if (m_Fade->GetFinish()) {
		if (m_NextIsTitle)
			Manager::SetScene <TitleScene>();
		if (m_NextIsGame)
			Manager::SetScene<GameScene>();
		if (m_NextIsExit)
			Manager::SetScene<ExitScene>();
	}

	
}
