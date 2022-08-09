#include "TitleScene.h"
#include "TitlePolygon.h"
#include "manager.h"
#include "GameScene.h"
#include "camera.h"
#include "Transition.h"
#include "GameObject_Invoke.h"

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
		m_SwitchToScenes = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPloygonTest>(16, 16, centerpos, 20.0f, 0.0f);
		for (auto switchscene : m_SwitchToScenes) {
			switchscene->GetComponent<VertexChangeComponent_ToGame>()->Init();
		}
	}

	//	上下のピンクと青のやつ
	{
		D3DXVECTOR3 centerpos = { 0.0f,0.0f,0.0f };
		centerpos.y = 10.0f;
		m_Circles.push_back(CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 0.0f));
		std::vector<CO_3DPolygon_circle*> circles = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 180.0f);
		for (CO_3DPolygon_circle* cir : circles) {
			cir->GetComponent<Polygon3DComponent>()->LoadTexture("asset\\texture\\circle_pink.png");
		}
		m_Circles.push_back(circles);

		centerpos.y = -10.0f;
		m_Circles.push_back(CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 0.0f));
		std::vector<CO_3DPolygon_circle*> circles_ = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 180.0f);
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
	game->SetPosition({ 0.0f,13.0f,30.0f });
	float gameslca = 7.5f;
	game->SetScale({ gameslca ,gameslca ,gameslca });




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

			m_Fade->Start(false);
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
			m_Confirmation = AddGameObject< CO_Confirmation>(LAYER_2D);
			return;
		}

		//	確認UIの結果-->Yesの場合のフェードスタート
		if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes())
		{
			m_Fade->Start(false);
		}

		//	確認UIの結果-->No の場合のフェードスタート
		if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes() == false) {
			m_Confirmation->SetDestroy();
			m_Confirmation = nullptr;
		}


		if (m_Fade->GetFinish() && istoexit) {
			Manager::SetScene <ExitScene>();
			return;
		}
	}

}
