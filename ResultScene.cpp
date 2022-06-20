#include "ResultScene.h"
#include "ResultPolygon.h"

void ResultScene::Init()
{
	AddGameObject<ResultPolygon>(LAYER_2D);
}
