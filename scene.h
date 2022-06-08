#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include <string>


#include "gameObject.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"
#include "player.h"
#include "Enemy.h"
#include "Item.h"
#include "light.h" 
#include "ao_Sphere.h"
#include "Bullet.h"
#include "ModelManager.h"

enum LAYER {
	LAYER_FIRST=0,
	LAYER_3D,
	LAYER_2D,
	LAYER_NUM_MAX,
};

class Scene
{
protected :
	std::list<GameObject*> m_GameObject[LAYER_NUM_MAX];
public:


	inline Scene() {}
	inline virtual ~Scene() {}

	inline virtual void Init()
	{
		

		AddGameObject<Camera>(LAYER_FIRST);

		AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));
					
		AddGameObject<Field>(LAYER_3D);
		
		AddGameObject<Player>(LAYER_3D);
		

		AddGameObject<Enemy>(LAYER_3D)->SetPosition(D3DXVECTOR3(0.0f, 0.5f, 5.0f));
		for (int i = 1; i <= 5; i++) 
		{
			AddGameObject<Enemy>(LAYER_3D)->SetPosition(D3DXVECTOR3(3.0f*i, 0.5f, 5.0f));
			AddGameObject<Enemy>(LAYER_3D)->SetPosition(D3DXVECTOR3(-3.0f*i, 0.5f, 5.0f));
		}
		
		

		AddGameObject<item>(LAYER_3D)->SetPosition(D3DXVECTOR3(-5.0f, 0.5f, 5.0f));
		AddGameObject<Ao_Sphere>(LAYER_3D);

		//AddGameObject<Bullet>();

		AddGameObject<Polygon2D>(LAYER_2D);

		
		Load();
	}

	inline void Load() {
		
		
		
	}

	inline void Unload() {
		//ModelManager::AllRelease();
		ResourceManger<Model>::AllRelease();
	}

	template <typename T>//テンプレート解放
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}


	template <typename T>
	T* GetGameObject() {
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (auto obj : m_GameObject[i]) {

				//	型を調べる(RTTI動的型情報)
				if (typeid(*obj) == typeid(T)) {
					return (T*)obj;
				}
			}
		}
		return nullptr;	
	}

	template <typename T>
	std::vector<T*> GetGameObjects() {
		std::vector<T*> objects;
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (auto obj : m_GameObject[i]) {

				//	型を調べる(RTTI動的型情報)
				if (typeid(*obj) == typeid(T)) {
					objects.push_back((T*)obj);
				}
			}
		}
		return objects;
	}

	inline virtual void UnInit()
	{
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();//リストのクリア
		}

		Unload();
	}

	inline virtual void Update()
	{
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}

	inline virtual void Draw()
	{
		for (int i = 0; i < LAYER_NUM_MAX; i++) {
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}
};


