#include "TitleScene.h"
#include "TitlePolygon.h"
#include "manager.h"
#include "GameScene.h"
#include "camera.h"
#include "Transition.h"
#include "GameObject_Invoke.h"

#include "audio.h"

#include "player.h"
#include "light.h"
#include "ImGuiObject_Title.h"
#include "CircleDeploy.h"
#include "CO_3DPolygon_circle.h"
#include "CO_TitleBackGround.h"
#include "ComponentObjectTest.h"
#include "CO_ToriiBlock.h"
#include "CO_toExit.h"
#include "CO_toGame.h"
#include "ExitScene.h"
#include "CO_Confirmation.h"
#include "CO_UI_Quest.h"
#include "CO_UI_Quest_Belt.h"
#include "CO_TitleObject.h"
#include "ParticleObject.h"
#include "CO_Noise.h"

void TitleScene::Init()
{
	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	プレイヤー
	AddGameObject<Player>(LAYER_3D)->SetIsNoMove();
	
	//	白い四角いやつ
	{
		D3DXVECTOR3 centerpos = { 0.0f,0.0f,0.0f };
		m_SwitchToScenes = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPloygonTest>(16, 16, centerpos, 20.0f, 0.0f,LAYER_3D);
		for (auto switchscene : m_SwitchToScenes) {
			switchscene->GetComponent<VertexChangeComponent_ToGame>()->Init();
		}
	}

	//	上下のピンクと青のやつ
	{
		D3DXVECTOR3 centerpos = { 0.0f,0.0f,0.0f };
		centerpos.y = 10.0f;
		m_Circles.push_back(CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 0.0f, LAYER_3D));
		std::vector<CO_3DPolygon_circle*> circles = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 180.0f, LAYER_3D);
		for (CO_3DPolygon_circle* cir : circles) {
			cir->GetComponent<Polygon3DComponent>()->LoadTexture("asset\\texture\\circle_pink.png");
		}
		m_Circles.push_back(circles);

		centerpos.y = -10.0f;
		m_Circles.push_back(CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 0.0f, LAYER_3D));
		std::vector<CO_3DPolygon_circle*> circles_ = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 180.0f, LAYER_3D);
		for (CO_3DPolygon_circle* cir : circles_) {
			cir->GetComponent<Polygon3DComponent>()->LoadTexture("asset\\texture\\circle_pink.png");
		}
		m_Circles.push_back(circles_);
	}

	//	背景の十字
	AddGameObject< CO_TitleBackGround>(LAYER_3D);

	

	//	鳥居 Exit
	AddGameObject< CO_ToriiBlock>(LAYER_3D)->SetPosition({ 0.0f,-7.5f,-30.0f });

	//	鳥居 Game
	AddGameObject< CO_ToriiBlock>(LAYER_3D)->SetPosition({ 0.0f,-7.5f,30.0f });

	//	Exitモデル
	auto* exit = AddGameObject < CO_toExit>(LAYER_3D);
	exit->SetPosition({ 0.0f,13.0f,-30.0f });
	exit->SetRotation({ MyMath::GetRadian(180.0f),0.0f,0.0f });
	
	//	Gameモデル
	auto* game = AddGameObject < CO_toGame>(LAYER_3D);
	game->SetPosition({ 0.0f,12.0f,30.0f });

	auto* title_object = AddGameObject< CO_TitleObject>(LAYER_3D);
	title_object->SetPosition({ 0.0f,15.0f,30.0f });

	//AddGameObject<CO_UI_Quest>(LAYER_2D);
	
	//float dest_y = 400.0f;
	//float dep_y = 800.0f;
	//{
	//	CO_UI_Quest_Belt* couibelt = AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
	//	couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y,0.0f });
	//	couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y,0.0f });
	//	couibelt->Start(false, 60, 60,true);
	//}

	//{
	//	float sep_y = 200.0f;
	//	CO_UI_Quest_Belt* couibelt = AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
	//	couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y + sep_y,0.0f });
	//	couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y + sep_y,0.0f });
	//	couibelt->Start(false, 60, 90,true);
	//}
	
	//	Audio
	m_BGM = AddGameObject<Audio>(LAYER_AUDIO);
	m_BGM->Load("asset\\audio\\BGM_Title.wav");
	m_BGM->Play(true);

	m_SESelect = AddGameObject<Audio>(LAYER_AUDIO);
	m_SESelect->Load("asset\\audio\\SE_Kettei2.wav");
	m_SESelect->SetAudioVolume(0.5f);
	
	m_Particle = AddGameObject<ParticleObject>(LAYER_3D);

	AddGameObject< CO_Noise>(LAYER_2D);

//	↑に追加
//--これ以降は追加しない-------------------------------------------------------------------
	AddGameObject<ImGuiObject_Title>(LAYER_3D);

	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);
}

void TitleScene::Update()
{
	Scene::Update();

	//	上下のピンクと青のやつ常時回転--->あとで別のゲームオブジェクトにやらせる。
	for (auto circle : m_Circles) {
		for (auto circle2 : circle) {
			D3DXVECTOR3 pos = circle2->GetPosition();

			float nsin = sinf(MyMath::GetRadian(m_Angle));
			float ncos = cosf(MyMath::GetRadian(m_Angle));

			float nx = ncos * pos.x - nsin * pos.z;
			float nz = nsin * pos.x + ncos * pos.z;

			pos.x = nx;
			pos.z = nz;
			circle2->SetPosition(pos);
		}
	}

	for(int i=0;i<2;i++)
		m_Particle->SetParticle_Title();


//	以下はシーン遷移処理なので、ゲームオブジェクトは「持たず、作らず、持ち込ませず」
	
	//	ゲームシーンへの遷移処理
	{
		//	Game方向の四角白が視野内ならtrue
		bool istogame = false;
		for (auto sts : m_SwitchToScenes)
		{
			if (sts->GetComponent<VertexChangeComponent_ToGame>()->GetIsToGameAndInside())
				istogame = true;
		}

		if (GetKeyboardTrigger(DIK_SPACE) && istogame) {
			for (int i = 0; i < 100; i++) {
				PARTICLE par;
				par.acc = { 0.0f,0.0f,0.0f };
				par.m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,0.5f };
				par.m_ColorOverLifeTime_End = { 0.0f,1.0f,1.0f,1.0f };
				par.col = par.m_ColorOverLifeTime_Start;
				par.life = 30;
				par.pos = { 0.0f,1.0f,0.0f };
				par.rot = { 0.0f,0.0f,0.0f };
				par.rot_vel = MyMath::VEC3Random(-0.01f, 0.01f);
				par.m_SizeOverLifeTime_Start = 0.5f;
				par.m_SizeOverLifeTime_End = 0.0f;
				par.size = par.m_SizeOverLifeTime_Start;
				par.status = 0;
				par.type = rand() % PARTICLE_TYPE_MAX;
				par.use = true;
				par.use_torii = false;
				par.vel = MyMath::VEC3Random(-0.5f, 0.5f);

				m_Particle->SetParticle(par);
			}
				
			m_Fade->Start(false);
			m_SESelect->Play(false);
		}


		if (m_Fade->GetFinish() && istogame) {
			Manager::SetScene <GameScene>();
			return;
		}
	}


	//	Exitシーンへの遷移処理
	{
		bool istoexit = false;
		for (auto sts : m_SwitchToScenes)
		{
			if (sts->GetComponent<VertexChangeComponent_ToGame>()->GetIsToExitAndInside()) {
				istoexit = true;
				break;
			}
		}

		//	確認UIの出現
		if (GetKeyboardTrigger(DIK_SPACE) && istoexit && m_Confirmation == nullptr) {
			m_SESelect->Play(false);
			m_Confirmation = AddGameObject< CO_Confirmation>(LAYER_2D);
			return;
		}

		//	確認UIの結果-->Yesの場合のフェードスタート
		if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes())
		{	
			m_SESelect->Play(false);
			m_Fade->Start(false);
		}

		//	確認UIの結果-->No の場合のフェードスタート
		if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes() == false) {
			m_SESelect->Play(false);
			m_Confirmation->SetDestroy();
			m_Confirmation = nullptr;
		}


		if (m_Fade->GetFinish() && istoexit) {
			Manager::SetScene <ExitScene>();
			return;
		}
	}

}
