#include "GameScene.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"
#include "player.h"
#include "Enemy.h"
#include "Item.h"
#include "light.h" 
#include "ao_Sphere.h"
#include "Bullet.h"
#include "ResourceManager.h"
#include "texture.h"
#include "stage_include.h"
#include "EnemyFactory.h"
#include "Cube2D.h"
#include "Collision.h"
#include "manager.h"
#include "ResultScene.h"
#include "audio.h"
#include "UI_Charge.h"
#include "Cylinder.h"
#include "UI_Score.h"
#include "UserInterface_Animation.h"
#include "Transition.h"
#include "ComponentObjectTest.h"
#include "ImGuiObject.h"
#include "CO_UI_AimLing.h"
#include "EnemyGenerate.h"
#include "CO_UI_Quest.h"
#include "CO_UI_Quest_Belt.h"
#include "CO_UI_Quest_Purpose.h"
#include "CO_EnemyWave.h"
#include "GameScene2.h"
#include "ParticleObject.h"
#include "HPComponent.h"
#include "DefeatScene.h"
#include "CO_UI_PlayerHPGauge.h"
#include "CO_UI_dot.h"
#include "CO_UI_Line.h"
#include "ParticleObject_2D.h"
#include "CO_Torii_Broken.h"
#include "CO_Stand.h"
#include "CO_Bow.h"


void GameScene::Init()
{
	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	フィールド
	//AddGameObject<Field>(LAYER_3D);

	//	プレイヤーの前に入れる
	AddGameObject<CO_UI_dot>(LAYER_2D);
	AddGameObject< CO_UI_PlayerHPGauge>(LAYER_2D);
	AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,55.0f,0.0f });
	AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,85.0f,0.0f });

	//	プレイヤー
	AddGameObject<Player>(LAYER_3D);


	//	アイテム
	AddGameObject<item>(LAYER_3D)->SetPosition(D3DXVECTOR3(-5.0f, 0.5f, 5.0f));

	//	AO球
	AddGameObject<Ao_Sphere>(LAYER_3D)->LoadModel("asset\\model\\ao_Sphere_omaga.obj");

	//	ステージ配置
	StageCorridorCreate();

	for (int i = -10; i < 10; i++)
	{

		AddGameObject < CO_Stand>(LAYER_3D)->SetPosition({2.5f,0.0f,23.0f * i});
	}
	

	AddGameObject<CO_UI_AimLing>(LAYER_2D);

	//	AddGameObject<Polygon2D>(LAYER_2D);
	AddGameObject<UI_Charge>(LAYER_2D);

	//	AddGameObject< UI_Score>(LAYER_2D);

	AddGameObject<Collision2D>(LAYER_2D);

	//	Audio
	m_BGM = AddGameObject<Audio>(LAYER_AUDIO);
	m_BGM->Load("asset\\audio\\193.wav");
	m_BGM->Play(true);
	m_BGM->SetAudioVolume(0.1f);

	//	m_BGM->SetSourceRate(270.0f);

	/*{
		GameObject* cyl = AddGameObject<Cylinder>(LAYER_3D);
		cyl->SetPosition({ 5.0f,0.0f,2.0f });
		cyl->SetScale({ 3.0f,3.0f,3.0f });
	}

	{
		GameObject* cyl = AddGameObject<Cylinder>(LAYER_3D);
		cyl->SetPosition({ 5.0f,0.0f,10.0f });
		cyl->SetScale({ 3.0f,6.0f,3.0f });
	}

	{
		GameObject* cyl = AddGameObject<Cylinder>(LAYER_3D);
		cyl->SetPosition({ 5.0f,0.0f,17.0f });
		cyl->SetScale({ 3.0f,9.0f,3.0f });
	}*/

	

	AddGameObject< ImGuiObject>(LAYER_3D);

	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);

	

	AddGameObject<EnemyGenerate>(LAYER_3D);

	

	
	AddGameObject<CO_UI_Quest>(LAYER_2D);
	AddGameObject< CO_UI_Quest_Purpose>(LAYER_2D);

	float dest_y = 400.0f;
	float dep_y = 800.0f;
	{
		CO_UI_Quest_Belt* couibelt = AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
		couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y,0.0f });
		couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y,0.0f });
		couibelt->Start(false, 60, 60);
	}

	{
		float sep_y = 200.0f;
		CO_UI_Quest_Belt* couibelt = AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
		couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y + sep_y,0.0f });
		couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y + sep_y,0.0f });
		couibelt->Start(false, 60, 90);
	}

	 m_EnemyWave = AddGameObject< CO_EnemyWave>(LAYER_3D);

	AddGameObject<CO_Torii_Broken>(LAYER_3D);

	m_Particle = AddGameObject<ParticleObject>(LAYER_3D);

	AddGameObject<ParticleObject_2D>(LAYER_2D);

	AddGameObject<CO_Bow>(LAYER_3D);

	AddGameObject<CO_Bow>(LAYER_3D)->SetPosition({ 0.0f,20.0f,-50.0f });

	m_IsPlayerDeath = false;
}


void GameScene::Uninit()
{


	Scene::UnInit();
}

void GameScene::Update()
{
	Scene::Update();

	
	m_Particle->SetParticle_ToriiBloken_Rising();

	if (m_EnemyWave != nullptr) {
		if (m_EnemyWave->GetIsStageClear()) {
			m_EnemyWave->SetIsStageClear(false);
			m_Fade->Start(false);
		}
	}

	if (GetGameObject<Player>()->GetComponent<HPComponent>()->GetIsDeath() &&
		m_IsPlayerDeath == false)
	{
		m_IsPlayerDeath = true;
		m_Fade->Start(false);
	}

	if (GetKeyboardPress(DIK_N))
	{
		for (auto x : m_GameObject[LAYER_AUDIO]) {
			Audio* audio = dynamic_cast<Audio*>(x);
			audio->VolumeDown(0.01f);

		}
	}
	if (GetKeyboardPress(DIK_M))
	{
		for (auto x : m_GameObject[LAYER_AUDIO]) {
			Audio* audio = dynamic_cast<Audio*>(x);
			audio->VolumeUp(0.01f);

		}

	}

	if (GetKeyboardPress(DIK_V))
	{
		m_BGM->PitchDown(1.0f);
	}
	if (GetKeyboardPress(DIK_B))
	{
		m_BGM->PitchUp(1.0f);
	}

	if (m_Fade->GetFinish() &&
		m_IsPlayerDeath)
	{
		Manager::SetScene<DefeatScene>();
		return;
	}

	if (m_Fade->GetFinish()) {
		Manager::SetScene <GameScene2>();
	}



	//#ifdef _DEBUG
	//	char* str = GetDebugStr();
	//	wsprintf(GetDebugStr(), "game");
	//	wsprintf(&str[strlen(str)], "sourceRate:%d , targetRate:%d ",
	//		(int)sourceRate,(int)targetRate);
	//	
	//	SetWindowText(GetWindow(), GetDebugStr());
	//#endif



	
}

void GameScene::StageCorridorCreate()
{
	//	廊下（廻廊）
	for (int i = 0; i < 10; i++)
	{
		GameObject* left = AddGameObject<stage_corridor>(LAYER_3D);
		GameObject* right = AddGameObject<stage_corridor>(LAYER_3D);


		left->SetPosition({ -25.0f,0,5.0f * (float)i - 10 });
		right->SetPosition({ 24.0f,0,5.0f * (float)i - 9.25f });

		if (i >= 8)continue;;

		GameObject* inside = AddGameObject<stage_corridor>(LAYER_3D);

		inside->SetPosition({ 5.0f * (float)i - 11.5f,0.0f,42.5f });
		inside->SetRotation({ 3.14f,0.0f,0.0f });
	}
	for (int i = 0; i < 10; i++)
	{
		GameObject* left = AddGameObject<stage_corridor>(LAYER_3D);
		GameObject* right = AddGameObject<stage_corridor>(LAYER_3D);


		left->SetPosition({ -25.0f,0,5.0f * -(float)i + 10 });
		right->SetPosition({ 24.0f,0,5.0f * -(float)i + 9.25f });

		if (i >= 8)continue;;

		GameObject* inside = AddGameObject<stage_corridor>(LAYER_3D);

		inside->SetPosition({ 5.0f * (float)i - 11.5f,0.0f,-42.5f });
		inside->SetRotation({ 3.14f,0.0f,0.0f });
	}

	{
		D3DXVECTOR3 corner_position[2] =
		{
			{-22.0f,0.0f,45.0f },
			{27.5f,0.0f,45.0f}
		};

		D3DXVECTOR3 corner_rotation[2] =
		{
			{3.14f / 2.0f,0.0f,0.0f},
			{3.14f,0.0f,0.0f}
		};

		//	廊下（廻廊）の角
		for (int i = 0; i < 2; i++) {
			GameObject* corner = AddGameObject<stage_corridor_corner>(LAYER_3D);

			corner->SetPosition(corner_position[i]);
			corner->SetRotation(corner_rotation[i]);
		}
	}

	{
		D3DXVECTOR3 corner_position[2] =
		{
			{-21.0f,0.0f,-39.5f },
			{26.0f,0.0f,-39.5f}
		};

		D3DXVECTOR3 corner_rotation[2] =
		{
			{0.0f,0.0f,0.0f},
			{-D3DX_PI / 2.0f,0.0f,0.0f}
		};

		//	廊下（廻廊）の角
		for (int i = 0; i < 2; i++) {
			GameObject* corner = AddGameObject<stage_corridor_corner>(LAYER_3D);

			corner->SetPosition(corner_position[i]);
			corner->SetRotation(corner_rotation[i]);
		}
	}

	//	下の水
	AddGameObject<stage_wator_field>(LAYER_3D);

	//	大鳥居
	{
		stage_otorii* ot = AddGameObject< stage_otorii>(LAYER_3D);
		ot->SetPosition({ 17.0f,0.0f,70.0f });
		ot->SetScale({ 5.0f,5.0f,5.0f });
	}
	{
		stage_otorii* ot = AddGameObject< stage_otorii>(LAYER_3D);
		ot->SetPosition({ -17.0f,0.0f,-70.0f });
		ot->SetScale({ 5.0f,5.0f,5.0f });
		ot->SetRotation({ D3DX_PI,0.0f,0.0f });
	}
}

