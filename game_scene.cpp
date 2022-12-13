//  ---------------------------------------------------------
//  GameScene [GameScene.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/05
//  ------------------------summary--------------------------
//  - GameScene 1
//	- ステージ1
//	- シーンを継承
//  ---------------------------------------------------------
#include "stdafx.h"
#include "game_scene.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "light.h" 
#include "ao_sphere.h"
#include "bullet.h"

#include "stage_include.h"
#include "enemy_factory.h"

#include "result_scene.h"
#include "audio.h"
#include "cylinder.h"
#include "ui_score.h"
#include "user_interface_animation.h"
#include "transition.h"
#include "component_object_test.h"
#include "imgui_object.h"
#include "enemy_generate.h"
#include "co_enemy_wave.h"
#include "game_scene2.h"
#include "particle_object.h"
#include "hp_component.h"
#include "defeat_scene.h"

#include "particle_object_2d.h"
#include "co_torii_broken.h"
#include "co_stand.h"
#include "co_bow.h"
#include "co_noise.h"
#include "switching_renderer.h"
#include "loading_scene.h"

// factory
#include "ui_factory.h"
#include "player_factory.h"

void GameScene::Load()
{
	// Loadの処理	


	// Model_variable
	ResourceManger<Model_variable>::GetResource("asset\\model\\particle_object.obj");
	ResourceManger<Model_variable>::GetResource("asset\\model\\particle_object_cube.obj");
	ResourceManger<Model_variable>::GetResource("asset\\model\\particle_object_sphere.obj");
	ResourceManger<Model_variable>::GetResource("asset\\model\\bow.obj");
	ResourceManger<Model_variable>::GetResource("asset\\model\\stone_white.obj");

	// Model
	ResourceManger<Model>::GetResource("asset\\model\\M_otorii.obj");
	ResourceManger<Model>::GetResource("asset\\model\\M_kairou.obj");
	ResourceManger<Model>::GetResource("asset\\model\\M_kairou_corner.obj");
	ResourceManger<Model>::GetResource("asset\\model\\bow_red.obj");
	ResourceManger<Model>::GetResource("asset\\model\\drum.obj");
	ResourceManger<Model>::GetResource("asset\\model\\bow.obj");
	ResourceManger<Model>::GetResource("asset\\model\\ao_Sphere_omaga.obj");
	ResourceManger<Model>::GetResource("asset\\model\\ao_Sphere_sinonome.obj");
	ResourceManger<Model>::GetResource("asset\\model\\ao_Sphere_sky.obj");
	ResourceManger<Model>::GetResource("asset\\model\\curtains.obj");
	ResourceManger<Model>::GetResource("asset\\model\\stand.obj");
	ResourceManger<Model>::GetResource("asset\\model\\arrow.obj");

	// パーティクルのモデル
	for (int i = 1; i <= 50; i++)
	{
		std::ostringstream oss;
		if (i <= 9) {
			oss << 0 << 0;
		}
		else if (i >= 10) {
			oss << 0;
		}

		oss << i;
		ResourceManger<Model_variable>::GetResource("asset\\model\\torii\\torii_broken_" + oss.str() + ".obj");
	}

	// Texture
	ResourceManger<Texture>::GetResource("asset\\texture\\effect_explosion.dds");
	ResourceManger<Texture>::GetResource("asset\\texture\\water.dds");
	ResourceManger<Texture>::GetResource("asset\\texture\\water1.dds");
	ResourceManger<Texture>::GetResource("asset\\texture\\wave0.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\wave1.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\wave2.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\omagadoki.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\Tutorial_charge.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\Tutorial_jump.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\Tutorial_move.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\Tutorial_ray_move.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\Tutorial_shoot.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\UI_black_belt.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\UI_blue_belt.png");

	ResourceManger<Texture>::GetResource("asset\\texture\\UI_Continue.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\UI_GiveUp.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\UI_Ling.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\UI_Points.png");

	ResourceManger<Texture>::GetResource("asset\\texture\\UI_red_belt.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\Line.dds");
	ResourceManger<Texture>::GetResource("asset\\texture\\Line_EndPoint.dds");

	ResourceManger<Texture>::GetResource("asset\\texture\\label.dds");
	ResourceManger<Texture>::GetResource("asset\\texture\\label_white.dds");
	ResourceManger<Texture>::GetResource("asset\\texture\\particle_circle.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\particle_circle_outline.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\particle_rect.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\particle_rect_outline.png");

	ResourceManger<Texture>::GetResource("asset\\texture\\particle_triangle.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\particle_triangle_outline.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\purpose.png");
	ResourceManger<Texture>::GetResource("asset\\texture\\pixelNoiseColor.png");



	// Shader
	for (auto file : VertexShader::GetFileNames()) {
		ResourceManger<VertexShader>::GetResource(file.second);
	}

	_loadFinish = true;
}

void GameScene::Init()
{
	AddGameObject<SwitchinRendererFactory>(LAYER_BEGIN);

	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	// プレイヤー
	AddGameObject<PlayerFactory>(LAYER_3D);

	//	AO球
	AddGameObject<Ao_Sphere>(LAYER_3D)->LoadModel("asset\\model\\ao_Sphere_omaga.obj");

	//	ステージ配置
	StageCorridorCreate();

	//	道
	for (int i = -10; i < 10; i++)
	{
		AddGameObject < CO_Stand>(LAYER_3D)->SetPosition({2.5f,0.0f,23.0f * i});
	}
	
	

	//	Audio
	m_BGM = AddGameObject<Audio>(LAYER_AUDIO);
	m_BGM->Load("asset\\audio\\BGM_Game1.wav");
	m_BGM->Play(true);
	m_BGM->SetAudioVolume(0.1f);

	

	AddGameObject< ImGuiObject>(LAYER_3D);

	//	シーン遷移
	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);

	//	EnemyGenerate
	AddGameObject<EnemyGenerate>(LAYER_3D);
		

	//	EnemyWave
	m_EnemyWave = AddGameObject< CO_EnemyWave>(LAYER_3D);

	//	鳥居の破片パーティクル
	AddGameObject<CO_Torii_Broken>(LAYER_3D);

	//	このシーンの3Dパーティクル
	m_Particle = AddGameObject<ParticleObject>(LAYER_3D);

	//	このシーンの2Dパーティクル
	AddGameObject<ParticleObject_2D>(LAYER_PARTICLE);

	// ui
	AddGameObject<UIGameSceneFactory>(LAYER_2D);

	//	装飾用弓矢
	AddGameObject<CO_Bow>(LAYER_3D);
	AddGameObject<CO_Bow>(LAYER_3D)->SetPosition({ 0.0f,20.0f,-50.0f });

	//	Noise Object
	AddGameObject<CO_Noise>(LAYER_3D)->SetScale({ 1.0f,1.0f,1.0f });

	Renderer::SetValiable({ 0.0f,1.0f,1.0f,1.0f });

	m_IsPlayerDeath = false;
}


void GameScene::Uninit()
{
	Scene::UnInit();
	_loadFinish = false;
}

void GameScene::Update()
{
	Scene::Update();

	//	常に鳥居破片パーティクルを発生させる
	m_Particle->SetParticle_ToriiBloken_Rising();

	//	ステージクリア管理
	if (m_EnemyWave != nullptr) {
		if (m_EnemyWave->GetIsStageClear()) {
			m_EnemyWave->SetIsStageClear(false);
			m_Fade->Start(false);
		}
	}

	//	プレイヤーの死亡＆敗北シーンへの遷移処理
	if (GetGameObject<Player>()->GetComponent<HPComponent>()->GetIsDeath() &&
		m_IsPlayerDeath == false)
	{
		m_IsPlayerDeath = true;
		m_Fade->Start(false);
	}

	//	音量調整用関数
	AudioUpdate();

	//	フェード処理
	if (m_Fade->GetFinish() &&
		m_IsPlayerDeath)
	{
		Manager::SetScene<DefeatScene>();
		return;
	}

	if (m_Fade->GetFinish()) {
		Manager::SetScene <GameScene2>();
	}	
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

void GameScene::AudioUpdate()
{
#ifdef _DEBUG
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
#endif // _DEBUG
}


