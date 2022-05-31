#pragma once
#include "gameObject.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"
#include "player.h"
#include <list>
#include <vector>
#include <typeinfo>
#include <string>
#include "Enemy.h"
#include "Item.h"


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

		AddGameObject<item>()->SetPosition(D3DXVECTOR3(-5.0f, 0.5f, 5.0f));

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
		for (auto obj : m_GameObject) {

			//	型を調べる(RTTI動的型情報)
			if (typeid(*obj) == typeid(T)) {
				return (T*)obj;
			}
		}
		return nullptr;	
	}

	template <typename T>
	std::vector<T*> GetGameObjects() {
		std::vector<T*> objects;
		for (auto obj : m_GameObject) {

			//	型を調べる(RTTI動的型情報)
			if (typeid(*obj) == typeid(T)) {
				objects.push_back((T*)obj);
			}
		}
		return objects;
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


