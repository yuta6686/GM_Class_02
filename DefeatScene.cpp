#include "DefeatScene.h"
#include "manager.h"
#include "TitleScene.h"
#include "Transition.h"
#include "ResultPolygon.h"
#include "CO_UI_Select.h"
#include "CO_Select.h"
#include "ExitScene.h"
#include "GameScene.h"
#include "CO_UI_Default.h"
#include "ParticleObject_2D.h"
#include "audio.h"
#include "SwitchingRenderer.h"
#include "rendering_texture.h"

void DefeatScene::Init()
{
	AddGameObject<SwitchingRenderer>(LAYER_BEGIN)
		->SetLayerNum(LAYER_BEGIN);

	AddGameObject<SwitchingRenderer>(LAYER_TO_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_TO_RENDERING_TEXTURE);

	AddGameObject<RenderingTexture>(LAYER_RENDERING_TEXTURE);

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
	uii._texture = "asset\\texture\\GameOver.png";
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
