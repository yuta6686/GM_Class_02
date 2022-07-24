#include "TitleScene.h"
#include "TitlePolygon.h"
#include "manager.h"
#include "GameScene.h"
#include "Transition.h"
#include "GameObject_Invoke.h"

void TitleScene::Init()
{
	AddGameObject<TitlePolygon>(LAYER_2D);
	m_Fade = AddGameObject<Transition>(LAYER_2D);


	m_Fade->Start(true);
}

void TitleScene::Update()
{
	Scene::Update();
	
	

	if (GetKeyboardTrigger(DIK_SPACE)) {
		
		
		m_Fade->Start(false);
	}


	if (m_Fade->GetFinish()) {
		Manager::SetScene <GameScene>();
	}
}
