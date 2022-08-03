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

void TitleScene::Init()
{
	//	ÉJÉÅÉâ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ÉâÉCÉg
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));


	AddGameObject<Player>(LAYER_3D)->SetIsNoMove();
	

	//	AddGameObject<TitlePolygon>(LAYER_2D);

	int numLayer = 16;
	D3DXVECTOR3 center = { 0.0f,0.0f,0.0f };
	float radius = 20.0f;
	float interval = 360.0f / static_cast<float>(numLayer);
	D3DXVECTOR3 circlePos = { 0.0f,1.0f,0.0f };
	for (int i = 0; i < numLayer; i++) {
		float angle =
			MyMath::GetRadian(static_cast<float>(i * interval));
		circlePos.x = radius * sinf(angle);
		circlePos.z = radius * cosf(angle);
		m_SwitchToScenes.push_back(AddGameObject<CO_3DPloygonTest>(LAYER_3D));
		m_SwitchToScenes[i]->SetPosition(circlePos);
	}

	AddGameObject<ImGuiObject_Title>(LAYER_3D);


	m_Fade = AddGameObject<Transition>(LAYER_2D);



	m_Fade->Start(true);
}

void TitleScene::Update()
{
	Scene::Update();
	
	bool istogame = false;
	for (auto sts : m_SwitchToScenes)
	{
		if (sts->GetComponent<VertexChangerComponent_Color>()->GetIsToGame())
			istogame = true;
	}
	if (GetKeyboardTrigger(DIK_SPACE) && istogame) {
				
		m_Fade->Start(false);
	}


	if (m_Fade->GetFinish()) {
		Manager::SetScene <GameScene>();
	}
}
