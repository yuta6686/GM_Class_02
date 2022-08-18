#include "GameScene2.h"


#include "light.h"
#include "field.h"
#include "player.h"
#include "Item.h"
#include "ao_Sphere.h"
#include "CO_UI_AimLing.h"
#include "audio.h"
#include "Transition.h"
#include "UI_Charge.h"
#include "UI_Score.h"
#include "ImGuiObject.h"
#include "CO_UI_Quest_Belt.h"
#include "CO_UI_Quest.h"
#include "CO_UI_Quest_Purpose.h"
#include "CO_EnemyWave.h"
#include "EnemyWave_2_1.h"

#include "ResultScene.h"
#include "stage_include.h"
#include "EnemyGenerate.h"
#include "GameScene3.h"
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

void GameScene2::Init()
{
	//	�J����
	AddGameObject<Camera>(LAYER_FIRST);

	//	���C�g
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	�t�B�[���h
	AddGameObject<Field>(LAYER_3D);

	//	�v���C���[�̑O�ɓ����
	AddGameObject<CO_UI_dot>(LAYER_2D);
	AddGameObject< CO_UI_PlayerHPGauge>(LAYER_2D);
	AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,55.0f,0.0f });
	AddGameObject< CO_UI_Line>(LAYER_2D)->SetPosition({ 0.0f,85.0f,0.0f });

	//	�v���C���[
	AddGameObject<Player>(LAYER_3D);


	//	�A�C�e��
	AddGameObject<item>(LAYER_3D)->SetPosition(D3DXVECTOR3(-5.0f, 0.5f, 5.0f));

	//	AO��
	AddGameObject<Ao_Sphere>(LAYER_3D)->LoadModel("asset\\model\\ao_Sphere_sinonome.obj");

	//	�X�e�[�W�z�u
	StageCorridorCreate();

	for (int i = -10; i < 10; i++)
	{

		AddGameObject < CO_Stand>(LAYER_3D)->SetPosition({ 2.5f,0.0f,23.0f * i });
	}

	AddGameObject<CO_UI_AimLing>(LAYER_2D);
	AddGameObject<UI_Charge>(LAYER_2D);
	
	

	//	Audio
	m_BGM = AddGameObject<Audio>(LAYER_AUDIO);
	m_BGM->Load("asset\\audio\\193.wav");
	m_BGM->Play(true);
	m_BGM->SetAudioVolume(0.1f);

	//	m_BGM->SetSourceRate(270.0f);

	//{
	//	GameObject* cyl = AddGameObject<Cylinder>(LAYER_3D);
	//	cyl->SetPosition({ 5.0f,0.0f,2.0f });
	//	cyl->SetScale({ 3.0f,3.0f,3.0f });
	//}

	//{
	//	GameObject* cyl = AddGameObject<Cylinder>(LAYER_3D);
	//	cyl->SetPosition({ 5.0f,0.0f,10.0f });
	//	cyl->SetScale({ 3.0f,6.0f,3.0f });
	//}

	//{
	//	GameObject* cyl = AddGameObject<Cylinder>(LAYER_3D);
	//	cyl->SetPosition({ 5.0f,0.0f,17.0f });
	//	cyl->SetScale({ 3.0f,9.0f,3.0f });
	//}





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
	m_EnemyWave->SetEnemyWave<EnemyWave_2_1>("asset\\file\\EnemyGenerate2-1.txt");

	m_Particle = AddGameObject<ParticleObject>(LAYER_3D);

	AddGameObject<ParticleObject_2D>(LAYER_2D);

	AddGameObject<CO_Bow>(LAYER_3D);

	AddGameObject<CO_Bow>(LAYER_3D)->SetPosition({ 0.0f,20.0f,-50.0f });

	Renderer::SetValiable({ 0.0f,1.0f,1.0f,1.0f });

	m_IsPlayerDeath = false;
}

void GameScene2::Uninit()
{
	Scene::UnInit();
}

void GameScene2::Update()
{
	Scene::Update();

	for (int i = 0; i < 2; i++)
		m_Particle->SetParticle_ToriiBloken_Rising();

	if (m_EnemyWave->GetIsStageClear()) {
		m_EnemyWave->SetIsStageClear(false);
		m_Fade->Start(false);
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
		Manager::SetScene <GameScene3>();
	}
}

void GameScene2::StageCorridorCreate()
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
	AddGameObject< stage_otorii>(LAYER_3D)->SetPosition({ 4.0f,0.0f,0.0f });
}
