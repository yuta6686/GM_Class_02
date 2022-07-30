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

void GameScene::Init()
{
	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	フィールド
	AddGameObject<Field>(LAYER_3D);

	//	プレイヤー
	AddGameObject<Player>(LAYER_3D);

	//	エネミー
	AddGameObject<Enemy>(LAYER_3D)->SetPosition(D3DXVECTOR3(0.0f, 0.5f, 5.0f));
	for (int i = 1; i <= 5; i++)
	{
		AddGameObject(EnemyFactory::Create<Enemy>(i * 5), LAYER_3D)->SetPosition(D3DXVECTOR3(3.0f * i, 0.5f, 5.0f));
		AddGameObject(EnemyFactory::Create<Enemy>(i * 10), LAYER_3D)->SetPosition(D3DXVECTOR3(-3.0f * i, 0.5f, 5.0f));

		AddGameObject(EnemyFactory::Create<Enemy>(i * 15), LAYER_3D)->SetPosition({ -3.0f * i, -0.5f, -5.0f });
	}

	//	アイテム
	AddGameObject<item>(LAYER_3D)->SetPosition(D3DXVECTOR3(-5.0f, 0.5f, 5.0f));

	//	AO球
	AddGameObject<Ao_Sphere>(LAYER_3D);

	//	ステージ配置
	StageCorridorCreate();

	AddGameObject<Polygon2D>(LAYER_2D);
	AddGameObject<UI_Charge>(LAYER_2D);

	AddGameObject< UI_Score>(LAYER_2D);
	//Cube2D* pcube2d_01 = AddGameObject<Cube2D>(LAYER_2D);
	//pcube2d_01->SetPosition({ -100.0f,1.0f,0.0f });
	//pcube2d_01->SetSpeed(D3DXVECTOR3(-5.0f, 10.0f, 0.0f));
	//pcube2d_01->SetRotation(MyMath::GetRadian({ 0.0f,0.0f,45.0f }));
	////pcube2d_01->SetzContinuousRotation(MyMath::GetRadian(-5.0f));

	//Cube2D* pcube2d_02 = AddGameObject<Cube2D>(LAYER_2D);
	//pcube2d_02->SetPosition({ 200.0f,-1.0f,0.0f });
	//pcube2d_02->SetSpeed(D3DXVECTOR3(50.0f, 4.0f, 0.0f));
	////pcube2d_02->SetzContinuousRotation(MyMath::GetRadian(1.0f));

	AddGameObject<Collision2D>(LAYER_2D);

	//	Audio
	m_BGM = AddGameObject<Audio>(LAYER_AUDIO);
	m_BGM->Load("asset\\audio\\kanatanouchuu.wav");
	m_BGM->Play(true);

	m_BGM->SetSourceRate(270.0f);

	{
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
	}

	AddGameObject<ComponentObjectTest>(LAYER_3D);
	AddGameObject< ImGuiObject>(LAYER_3D);

	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);

	AddGameObject<CO_UI_AimLing>(LAYER_2D);
}


void GameScene::Uninit()
{


	Scene::UnInit();
}

void GameScene::Update()
{
	Scene::Update();



	if (GetKeyboardTrigger(DIK_RETURN)) {
		m_Fade->Start(false);
	}

	if (GetKeyboardPress(DIK_N)) 
	{		
		m_BGM->VolumeDown(0.01f);
	}
	if (GetKeyboardPress(DIK_M))
	{	
		m_BGM->VolumeUp(0.01f);
	}

	if (GetKeyboardPress(DIK_V))
	{
		m_BGM->PitchDown(1.0f);
		
	}
	if (GetKeyboardPress(DIK_B))
	{
		m_BGM->PitchUp(1.0f);
		
	}

	if (m_FadeIn) {
		if (m_FadeIn->GetIsFinishFadeIn()) {
			m_FadeIn->SetDestroy();
		}
	}

	if (m_FadeOut) {
		if (m_FadeOut->GetIsTransition()) {
			m_FadeOut->SetDestroy();
			Manager::SetScene <ResultScene>();
		}
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
{//	廊下（廻廊）
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

	//	下の水
	AddGameObject<stage_wator_field>(LAYER_3D);

	//	大鳥居
	AddGameObject< stage_otorii>(LAYER_3D);
}

