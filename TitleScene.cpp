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
	//	ÉJÉÅÉâ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ÉâÉCÉg
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));


	AddGameObject<Player>(LAYER_3D)->SetIsNoMove();
	

	//	AddGameObject<TitlePolygon>(LAYER_2D);
	

	D3DXVECTOR3 centerpos = { 0.0f,0.0f,0.0f };
	m_SwitchToScenes = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPloygonTest>(16, 16, centerpos, 20.0f,0.0f);
	for (auto switchscene : m_SwitchToScenes) {
		switchscene->GetComponent<VertexChangeComponent_ToGame>()->Init();
	}


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

	AddGameObject< CO_TitleBackGround>(LAYER_3D);

	AddGameObject< CO_ToriiBlock>(LAYER_3D)->SetPosition({ 0.0f,-7.5f,-30.0f });
	AddGameObject< CO_ToriiBlock>(LAYER_3D)->SetPosition({ 0.0f,-7.5f,30.0f });

	auto* exit = AddGameObject < CO_toExit>(LAYER_3D);
	exit->SetPosition({ 0.0f,13.0f,-30.0f });
	exit->SetRotation({ MyMath::GetRadian(180.0f),0.0f,0.0f });
	
	auto* game = AddGameObject < CO_toGame>(LAYER_3D);
	game->SetPosition({ 0.0f,13.0f,30.0f });
	float gameslca = 7.5f;
	game->SetScale({ gameslca ,gameslca ,gameslca });

	
	
	AddGameObject<ImGuiObject_Title>(LAYER_3D);

	m_Fade = AddGameObject<Transition>(LAYER_2D);



	m_Fade->Start(true);
}

void TitleScene::Update()
{
	Scene::Update();

	//	âÒì]
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

	bool istoexit = false;
	for (auto sts : m_SwitchToScenes)
	{
		if (sts->GetComponent<VertexChangeComponent_ToGame>()->GetIsToExitAndInside()) {
			istoexit = true;
			break;
		}
			
	}

	if (GetKeyboardTrigger(DIK_SPACE) && istoexit && m_Confirmation == nullptr) {
		m_Confirmation = AddGameObject< CO_Confirmation>(LAYER_2D);		
		return;
	}

	if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes())
	{
		m_Fade->Start(false);
	}

	if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes()==false) {
		m_Confirmation->SetDestroy();		
		m_Confirmation = nullptr;
	}


	if (m_Fade->GetFinish() && istoexit) {
		Manager::SetScene <ExitScene>();
		return;
	}



}
