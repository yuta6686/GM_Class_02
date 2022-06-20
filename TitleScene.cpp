#include "TitleScene.h"
#include "TitlePolygon.h"
#include "manager.h"
#include "GameScene.h"

void TitleScene::Init()
{
	AddGameObject<TitlePolygon>(LAYER_2D);
}

void TitleScene::Update()
{
	Scene::Update();

	if (GetKeyboardTrigger(DIK_RETURN)) 
	{
		Manager::SetScene <GameScene>();
	}
}
