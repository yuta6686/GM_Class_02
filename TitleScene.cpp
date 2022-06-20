#include "TitleScene.h"
#include "TitlePolygon.h"

void TitleScene::Init()
{
	AddGameObject<TitlePolygon>(LAYER_2D);
}
