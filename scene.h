#pragma once
#include "gameObject.h"
#include "polygon2D.h"
#include "camera.h"
#include "player.h"

#include "field.h"
#include "Enemy.h"
#include "Bullet.h"

#include <list>
class Scene
{
protected:
	std::list<GameObject*> m_GameObjects;

public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Init() {
		AddGameObject<Camera>();
		AddGameObject<Field>();
		AddGameObject<Player>();
		

		AddGameObject<Enemy>()->SetPosition({ -3,5,0 });
		AddGameObject<Enemy>()->SetPosition({ 0,7,0 });
		AddGameObject<Enemy>()->SetPosition({ 3,-5,0 });

		//AddGameObject<Bullet>();

		//AddGameObject<Polygon2D>();
	}

	//	Œ^‚ğˆø”‚Æ‚µ‚Ä“n‚·‚±‚Æ‚ª‚Å‚«‚éB
	template <typename T>
	T* AddGameObject()
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObjects.push_back(gameObject);
		return gameObject;
	}

	virtual void Uninit()
	{
		for (auto obj : m_GameObjects) {
			obj->Uninit();
			delete obj;
		}
		m_GameObjects.clear();
	}

	virtual void Update() {
		for (auto obj : m_GameObjects) {
			obj->Update();
		}

		m_GameObjects.remove_if([](GameObject* obj) {
			return obj->Destroy();
		});
	}

	virtual void Draw() {
		for (auto obj : m_GameObjects) {
			obj->Draw();
		}
	}
};

