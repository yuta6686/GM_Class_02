#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include <string>

#include "ResourceManager.h"
#include "gameObject.h"


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

	inline virtual void Init() = 0;

	inline void Unload() {			
		ResourceManger<Model>::AllRelease();
		ResourceManger<Texture>::AllRelease();
		ResourceManger<VertexShader>::AllRelease();
		ResourceManger<PixelShader>::AllRelease();
		
	}
	GameObject* AddGameObject(GameObject* pGameObject,int layer) 
	{
		pGameObject->Init();
		m_GameObject[layer].push_back(pGameObject);
		return pGameObject;
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

		//Unload();
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

private:
	
	

};


