#include "TitleScene.h"
#include "TitlePolygon.h"
#include "manager.h"
#include "GameScene.h"
#include "Transition.h"
#include "GameObject_Invoke.h"

void TitleScene::Init()
{
	AddGameObject<TitlePolygon>(LAYER_2D);
	m_FadeIn = AddGameObject<Transition>(LAYER_2D);


	m_FadeIn->SetFadeIn();
}

void TitleScene::Update()
{
	Scene::Update();
	
	

	if (GetKeyboardTrigger(DIK_SPACE)) {
		m_FadeOut = AddGameObject<Transition>(LAYER_2D);
		
		m_FadeOut->SetFadeOut();
	}

	if (m_FadeIn) {
		if (m_FadeIn->GetIsFinishFadeIn()) {
			m_FadeIn->SetDestroy();
		}
	}

	if (m_FadeOut) {
		if (m_FadeOut->GetIsTransition()) {
			m_FadeOut->SetDestroy();
			Manager::SetScene <GameScene>();
		}
	}
}
