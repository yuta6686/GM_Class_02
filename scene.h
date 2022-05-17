#pragma once
#include "gameObject.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"
#include "player.h"
#include <list>
#include <string>


class Scene
{
public:
	Scene()=default;
	~Scene() = default;

	

	virtual void Init() {		
		Add2D(new Polygon2D());

		Add3D(Camera::Instance());
		Add3D(new Field());
		Add3D(new Player());


		for (auto x : g_2DGameObjects)
			x->Init();

		for (auto x : g_3DGameObjects)
			x->Init();
	}
	virtual void Uninit() {
		for (auto x : g_2DGameObjects) {
			x->Uninit();
			delete x;
			x = nullptr;
		}


		for (auto x : g_3DGameObjects) {
			x->Uninit();
			delete x;
			x = nullptr;
		}

	}
	virtual void Update() {
		for (auto x : g_2DGameObjects)
			x->Update();

		for (auto x : g_3DGameObjects)
			x->Update();

	}
	virtual void Draw() {
		//	êÊÇ…3Dï`âÊÇµÇ»Ç¢Ç∆Ç¢ÇØÇ»Ç¢ÇÁÇµÇ¢ÅB	
		Draw3D();

		Draw2D();
	}

	void Add2D(GameObject* other) {
		if (other == nullptr)return;
		g_2DGameObjects.push_back(other);
	}

	void Add3D(GameObject* other) {
		if (other == nullptr)return;
		g_3DGameObjects.push_back(other);
	}
	
protected:
	std::list<GameObject*> g_3DGameObjects;
	std::list<GameObject*> g_2DGameObjects;

	void Draw2D() {
		for (auto x : g_2DGameObjects)
			x->Draw();
	}
	void Draw3D() {
		for (auto x : g_3DGameObjects)
			x->Draw();
	}
};


