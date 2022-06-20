#pragma once
#include "polygon2D.h"
#include "scene.h"

enum SCENE {
	SCENE_TITLE = 0,
	SCENE_GAME,
	SCENE_RESULT,
};

class Manager
{
private:	

	static class std::shared_ptr<Scene> m_Scene;
public:
	//������
	static void Init();

	//�I������
	static void Uninit();

	//�X�V����
	static void Update();

	//�`�揈��
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
};