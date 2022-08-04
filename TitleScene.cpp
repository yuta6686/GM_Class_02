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

void TitleScene::Init()
{
	//	ÉJÉÅÉâ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ÉâÉCÉg
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));


	AddGameObject<Player>(LAYER_3D)->SetIsNoMove();
	

	//	AddGameObject<TitlePolygon>(LAYER_2D);
	

	D3DXVECTOR3 centerpos = { 0.0f,0.0f,0.0f };
	m_SwitchToScenes = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPloygonTest>(16, 16, centerpos, 20.0f);

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
		if (sts->GetComponent<VertexChangeComponent_ToGame>()->GetIsToGame())
			istogame = true;
	}
	if (GetKeyboardTrigger(DIK_SPACE) && istogame) {
				
		m_Fade->Start(false);
	}


	if (m_Fade->GetFinish()) {
		Manager::SetScene <GameScene>();
	}
}
