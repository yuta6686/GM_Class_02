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
	//������
	static void Init();

	//�I������
	static void Uninit();

	//�X�V����
	static void Update();

	//�`�揈��
	static void Draw();

	static class Scene* GetScene() { return m_Scene; }

};