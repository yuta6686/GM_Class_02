#include "ResultScene.h"
#include "ResultPolygon.h"
#include "manager.h"
#include "TitleScene.h"
#include "Transition.h"

void ResultScene::Init()
{
	AddGameObject<ResultPolygon>(LAYER_2D);
	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);

	Renderer::SetValiable({ 0.0f,1.0f,1.0f,1.0f });
}

void ResultScene::Update()
{
	Scene::Update();

	if (GetKeyboardTrigger(DIK_RETURN)) {	
		m_Fade->Start(false);
	}

	if (m_Fade->GetFinish()) {
		Manager::SetScene <TitleScene>();
	}

	
}
