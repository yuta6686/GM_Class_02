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

void GameScene2::Init()
{
	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	フィールド
	AddGameObject<Field>(LAYER_3D);

	//	プレイヤー
	AddGameObject<Player>(LAYER_3D);


	//	アイテム
	AddGameObject<item>(LAYER_3D)->SetPosition(D3DXVECTOR3(-5.0f, 0.5f, 5.0f));

	//	AO球
	AddGameObject<Ao_Sphere>(LAYER_3D);

	//	ステージ配置
	StageCorridorCreate();

	AddGameObject<CO_UI_AimLing>(LAYER_2D);

	AddGameObject<Polygon2D>(LAYER_2D);
	AddGameObject<UI_Charge>(LAYER_2D);

	AddGameObject< UI_Score>(LAYER_2D);
	

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



	// AddGameObject<EnemyGenerate>(LAYER_3D);




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
}

void GameScene2::Uninit()
{
}

void GameScene2::Update()
{
}

void GameScene2::StageCorridorCreate()
{
}
