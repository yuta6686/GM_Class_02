//  ---------------------------------------------------------
//  GameScene [GameScene.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/05
//  ------------------------summary--------------------------
//  - GameScene 1
//	- �X�e�[�W1
//	- �V�[�����p��
//  ---------------------------------------------------------
#include "game_scene.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "light.h" 
#include "ao_sphere.h"
#include "bullet.h"
#include "ResourceManager.h"
#include "stage_include.h"
#include "enemy_factory.h"
#include "Collision.h"
#include "manager.h"
#include "result_scene.h"
#include "audio.h"
#include "UI_Charge.h"
#include "cylinder.h"
#include "UI_Score.h"
#include "UserInterface_Animation.h"
#include "transition.h"
#include "component_object_test.h"
#include "ImGuiObject.h"
#include "co_ui_aimling.h"
#include "enemy_generate.h"
#include "co_ui_quest.h"
#include "co_ui_quest_belt.h"
#include "co_ui_quest_purpose.h"
#include "co_enemy_wave.h"
#include "game_scene2.h"
#include "particle_object.h"
#include "hp_component.h"
#include "defeat_scene.h"
#include "co_ui_player_hp_gauge.h"
#include "co_ui_dot.h"
#include "co_ui_line.h"
#include "particle_object_2d.h"
#include "co_torii_broken.h"
#include "co_stand.h"
#include "co_bow.h"
#include "co_ui_tutorial_move.h"
#include "CO_Noise.h"
#include "co_ui_tutorial_move2.h"
#include "SwitchingRenderer.h"
#include "rendering_texture.h"

void GameScene::Init()
{
	AddGameObject<SwitchingRenderer>(LAYER_BEGIN)
		->SetLayerNum(LAYER_BEGIN);

	AddGameObject<SwitchingRenderer>(LAYER_TO_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_TO_RENDERING_TEXTURE);

	AddGameObject<RenderingTexture>(LAYER_RENDERING_TEXTURE);

	//	�J����
	AddGameObject<Camera>(LAYER_FIRST);

	//	���C�g
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	�v���C���[�̑O�ɓ����
	AddGameObject<CO_UI_dot>(LAYER_2D);
	AddGameObject< CO_UI_PlayerHPGauge>(LAYER_2D);
	AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,55.0f,0.0f });
	AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,85.0f,0.0f });

	//	�v���C���[
	AddGameObject<Player>(LAYER_3D)->SetPosition({ 2.5f,5.0f,0.0f });		

	//	AO��
	AddGameObject<Ao_Sphere>(LAYER_3D)->LoadModel("asset\\model\\ao_Sphere_omaga.obj");

	//	�X�e�[�W�z�u
	StageCorridorCreate();

	//	��
	for (int i = -10; i < 10; i++)
	{
		AddGameObject < CO_Stand>(LAYER_3D)->SetPosition({2.5f,0.0f,23.0f * i});
	}
	
	//	User Interface
	AddGameObject<CO_UI_AimLing>(LAYER_2D);
	
	AddGameObject<UI_Charge>(LAYER_2D);

	AddGameObject<Collision2D>(LAYER_2D);

	//	Audio
	m_BGM = AddGameObject<Audio>(LAYER_AUDIO);
	m_BGM->Load("asset\\audio\\BGM_Game1.wav");
	m_BGM->Play(true);
	m_BGM->SetAudioVolume(0.1f);

	

	AddGameObject< ImGuiObject>(LAYER_3D);

	//	�V�[���J��
	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);

	//	EnemyGenerate
	AddGameObject<EnemyGenerate>(LAYER_3D);
	
	//	UserInterface 
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

	//	EnemyWave
	//m_EnemyWave = AddGameObject< CO_EnemyWave>(LAYER_3D);

	//	�����̔j�Ѓp�[�e�B�N��
	AddGameObject<CO_Torii_Broken>(LAYER_3D);

	//	���̃V�[����3D�p�[�e�B�N��
	m_Particle = AddGameObject<ParticleObject>(LAYER_3D);

	//	���̃V�[����2D�p�[�e�B�N��
	AddGameObject<ParticleObject_2D>(LAYER_PARTICLE);

	//	�����p�|��
	AddGameObject<CO_Bow>(LAYER_3D);
	AddGameObject<CO_Bow>(LAYER_3D)->SetPosition({ 0.0f,20.0f,-50.0f });

	//	UI
	AddGameObject< CO_UI_Tutorial_Move>(LAYER_2D);

	//	Noise Object
	AddGameObject<CO_Noise>(LAYER_3D)->SetScale({ 1.0f,1.0f,1.0f });

	Renderer::SetValiable({ 0.0f,1.0f,1.0f,1.0f });

	m_IsPlayerDeath = false;
}


void GameScene::Uninit()
{
	Scene::UnInit();
}

void GameScene::Update()
{
	Scene::Update();

	//	��ɒ����j�Ѓp�[�e�B�N���𔭐�������
	m_Particle->SetParticle_ToriiBloken_Rising();

	//	�X�e�[�W�N���A�Ǘ�
	if (m_EnemyWave != nullptr) {
		if (m_EnemyWave->GetIsStageClear()) {
			m_EnemyWave->SetIsStageClear(false);
			m_Fade->Start(false);
		}
	}

	//	�v���C���[�̎��S���s�k�V�[���ւ̑J�ڏ���
	if (GetGameObject<Player>()->GetComponent<HPComponent>()->GetIsDeath() &&
		m_IsPlayerDeath == false)
	{
		m_IsPlayerDeath = true;
		m_Fade->Start(false);
	}

	//	���ʒ����p�֐�
	AudioUpdate();

	//	�t�F�[�h����
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
	//	�L���i���L�j
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

		//	�L���i���L�j�̊p
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

		//	�L���i���L�j�̊p
		for (int i = 0; i < 2; i++) {
			GameObject* corner = AddGameObject<stage_corridor_corner>(LAYER_3D);

			corner->SetPosition(corner_position[i]);
			corner->SetRotation(corner_rotation[i]);
		}
	}

	//	���̐�
	AddGameObject<stage_wator_field>(LAYER_3D);

	//	�咹��
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

