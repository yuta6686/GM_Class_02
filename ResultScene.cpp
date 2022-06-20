#include "ResultScene.h"
#include "ResultPolygon.h"
#include "manager.h"
#include "TitleScene.h"

void ResultScene::Init()
{
	AddGameObject<ResultPolygon>(LAYER_2D);
}

void ResultScene::Update()
{
	Scene::Update();

	if (GetKeyboardTrigger(DIK_RETURN)) {
		Manager::SetScene<TitleScene>();
	}
}
