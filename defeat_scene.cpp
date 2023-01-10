#include "defeat_scene.h"

#include "title_scene.h"
#include "transition.h"
#include "result_polygon.h"
#include "co_ui_select.h"
#include "co_select.h"
#include "exit_scene.h"
#include "game_scene.h"
#include "co_ui_default.h"
#include "particle_object_2d.h"
#include "audio.h"
#include "switching_renderer.h"
#include "co_bow.h"
#include "resource_manager.h"
#include "blink_scale_component.h"

void DefeatScene::Init()
{
	AddGameObject<SwitchinRendererFactory>(LAYER_BEGIN);

	AddGameObject<CO_Bow>(LAYER_3D);

	AddGameObject<ResultPolygon>(LAYER_2D);
	

	for (int i = 0; i < 3; i++) {
		AddGameObject<CO_UI_Select>(LAYER_2D)
			->SetTrue_False_Position({ SCREEN_WIDTH/2.0f,700.0f + 70.0f * i,0.0f },0.0f);
	}
	for (int i = 0; i < 3; i++) {
		CO_UI_Select* select = AddGameObject<CO_UI_Select>(LAYER_2D);
		select->SetTrue_False_Position({ SCREEN_WIDTH / 2.0f+100.0f,700.0f + 70.0f * i,0.0f },10.0f);
		select->SetIsString();
		select->GetComponent<UserInterfaceComponent>()->
			LoadTexture(CO_UI_Select::GetFileName_Box()[i]);		
	}

	//	CO_UI_Select‚Ì‚ ‚Æ‚É‚â‚é
	m_Select = AddGameObject< CO_Select>(LAYER_2D);
	//	m_Select->SetBlue(true);

	m_NextIsExit = false;
	m_NextIsGame = false;
	m_NextIsTitle = false;
	m_ChangeScene = false;

	UI_Information uii;
	uii._deploy_index = DEPLOY_CENTER;
	uii._texture = "asset\\texture\\GameOver.dds";
	uii._main_pos = { 200.0f ,50.0f,0.0f};

	CO_UI_Default* ui2d = AddGameObject< CO_UI_Default>(LAYER_2D);
	ui2d->SetUIInfo(uii, { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f - 100.0f,0.0f });
	ui2d->AddComponent<BlinkComponent_Scale>(COMLAYER_SECOND)->SetParameter(AXIS_XY, 0.1f, 1.0f, 1.5f);

	m_Particle = AddGameObject<ParticleObject_2D>(LAYER_2D);

	Renderer::SetValiable({ 0.0f,1.0f,1.0f,1.0f });

	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);

	m_BGM = Manager::GetScene()->AddGameObject<Audio>(LAYER_AUDIO);
	m_BGM->Load("asset\\audio\\BGM_GameOver.wav");
	m_BGM->Play(true);
}

void DefeatScene::Update()
{
	m_Particle->SetParticle_Descent({ 1.0f,0.0f,0.0f,0.0f });

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
		//	‰½‚à‚µ‚È‚¢
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
