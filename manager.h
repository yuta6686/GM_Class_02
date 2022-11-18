#pragma once
#include "polygon2d.h"
#include "scene.h"

enum SCENE {
	SCENE_TITLE = 0,
	SCENE_GAME,
	SCENE_RESULT,
};

class RenderingTexture;
class Manager
{
private:	
	inline static bool m_IsExit = false;
	static class std::shared_ptr<Scene> m_Scene;
	inline static RenderingTexture* _rt = nullptr;
public:
	//初期化
	static void Init();

	//終了処理
	static void Uninit();

	//更新処理
	static void Update();

	//描画処理
	static void Draw();
	

	static class std::shared_ptr<Scene> GetScene()
	{
		return m_Scene;
	}

	template <typename T>
	static void SetScene() 
	{
		if (m_Scene) 
		{
			m_Scene->UnInit();
		}
		
		m_Scene = std::make_shared<T>();
		m_Scene->Init();
	}

	static void SetIsExit(const bool& flag) { m_IsExit = flag; }
	static bool GetIsExit() { return m_IsExit; }
};