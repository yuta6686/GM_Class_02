#pragma once
#include "gameObject.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"
#include "player.h"
#include <list>
#include <string>
#include "Enemy.h"


class Scene
{
protected :
	std::list<GameObject*> m_GameObject;
public:


	Scene() {}
	virtual ~Scene() {}

	virtual void Init()
	{
		AddGameObject<Camera>();
		AddGameObject<Field>();
		AddGameObject<Player>();

		AddGameObject<Enemy>()->SetPosition(D3DXVECTOR3(0.0f, 0.5f, 5.0f));
		AddGameObject<Enemy>()->SetPosition(D3DXVECTOR3(3.0f, 0.5f, 5.0f));
		AddGameObject<Enemy>()->SetPosition(D3DXVECTOR3(-3.0f, 0.5f, 5.0f));



		//AddGameObject<Bullet>();

		//AddGameObject<Polygon2D>();
	}

	template <typename T>//テンプレート解放
	T* AddGameObject()
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject.push_back(gameObject);

		return gameObject;
	}

	template <typename T>
	T* GetGameObject() {
		for (auto* obj : m_GameObject) {
			if (typeid(*obj) == typeid(T)) {
				return (T*)obj;
			}
		}
		return nullptr;	
	}

	virtual void UnInit()
	{
		for (GameObject* object : m_GameObject)
		{
			object->Uninit();
			delete object;
		}
		m_GameObject.clear();//リストのクリア
	}

	virtual void Update()
	{
		for (GameObject* object : m_GameObject)
		{
			object->Update();
		}

		m_GameObject.remove_if([](GameObject* object) {return object->Destroy(); });
	}

	virtual void Draw()
	{
		for (GameObject* object : m_GameObject)
		{
			object->Draw();
		}
	}
};


