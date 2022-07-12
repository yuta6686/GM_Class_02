#include "ResultScene.h"
#include "ResultPolygon.h"
#include "manager.h"
#include "TitleScene.h"
#include "Transition.h"

void ResultScene::Init()
{
	AddGameObject<ResultPolygon>(LAYER_2D);
	m_FadeIn = AddGameObject<Transition>(LAYER_2D);
	m_FadeIn->SetFadeIn();
}

void ResultScene::Update()
{
	Scene::Update();

	if (GetKeyboardTrigger(DIK_RETURN)) {
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
			Manager::SetScene <TitleScene>();
		}
	}
}
