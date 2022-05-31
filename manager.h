#pragma once
#include "polygon2D.h"


class Manager
{
private:
	static class Scene* m_Scene;

public:
	//‰Šú‰»
	static void Init();

	//I—¹ˆ—
	static void Uninit();

	//XVˆ—
	static void Update();

	//•`‰æˆ—
	static void Draw();

	static class Scene* GetScene() { return m_Scene; }

};