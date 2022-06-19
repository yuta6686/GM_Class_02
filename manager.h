#pragma once
#include "polygon2D.h"

enum SCENE {
	SCENE_TITLE = 0,
	SCENE_GAME,
	SCENE_RESULT,
};

class Manager
{
private:
	static class Scene* m_Scene;

public:
	//初期化
	static void Init();

	//終了処理
	static void Uninit();

	//更新処理
	static void Update();

	//描画処理
	static void Draw();

	static class Scene* GetScene() { return m_Scene; }

};