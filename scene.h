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
#include "ResourceManager.h"
#include "texture.h"
#include "stage_include.h"
#include "EnemyFactory.h"
#include "Cube2D.h"
#include "Collision.h"

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
			AddGameObject(EnemyFactory::Create<Enemy>(i*5), LAYER_3D)->SetPosition(D3DXVECTOR3(3.0f*i, 0.5f, 5.0f));
			AddGameObject(EnemyFactory::Create<Enemy>(i*10), LAYER_3D)->SetPosition(D3DXVECTOR3(-3.0f*i, 0.5f, 5.0f));

			AddGameObject(EnemyFactory::Create<Enemy>(i*15), LAYER_3D)->SetPosition({ -3.0f * i, -0.5f, -5.0f });
		}
		
		

		AddGameObject<item>(LAYER_3D)->SetPosition(D3DXVECTOR3(-5.0f, 0.5f, 5.0f));
		AddGameObject<Ao_Sphere>(LAYER_3D);

		//	ステージ配置
		StageCorridorCreate();			

		AddGameObject<Polygon2D>(LAYER_2D);

		Cube2D* pcube2d_01 = AddGameObject<Cube2D>(LAYER_2D);
		pcube2d_01->SetPosition({ -100.0f,1.0f,0.0f });
		pcube2d_01->SetSpeed(D3DXVECTOR3(-10.0f,0.0f,0.0f));

		Cube2D* pcube2d_02 = AddGameObject<Cube2D>(LAYER_2D);
		pcube2d_02->SetPosition({ 200.0f,-1.0f,0.0f });
		pcube2d_02->SetSpeed(D3DXVECTOR3(5.0f, 0.0f,0.0f));

		AddGameObject<Collision2D>(LAYER_2D);
		
		Load();
	}

	inline void Load() {
		
		
		
	}

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

private:
	
	void StageCorridorCreate() 
	{
		//	廊下（廻廊）
		for (int i = 0; i < 10; i++) 
		{
			GameObject* left = AddGameObject<stage_corridor>(LAYER_3D);
			GameObject* right = AddGameObject<stage_corridor>(LAYER_3D);
			

			left->SetPosition({ -25.0f,0,5.0f * (float)i - 10 });
			right->SetPosition({ 24.0f,0,5.0f * (float)i - 9.25f });

			if (i >= 8)continue;;

			GameObject* inside = AddGameObject<stage_corridor>(LAYER_3D);

			inside->SetPosition({ 5.0f * (float)i-11.5f,0.0f,42.5f });
			inside->SetRotation({3.14f,0.0f,0.0f});
		}

		D3DXVECTOR3 corner_position[2] =
		{
			{-22.0f,0.0f,45.0f },
			{27.5f,0.0f,45.0f}
		};

		D3DXVECTOR3 corner_rotation[2] =
		{
			{3.14f / 2.0f,0.0f,0.0f},
			{3.14f,0.0f,0.0f}
		};
		
		//	廊下（廻廊）の角
		for (int i = 0; i < 2; i++) {
			GameObject* corner = AddGameObject<stage_corridor_corner>(LAYER_3D);

			corner->SetPosition(corner_position[i]);
			corner->SetRotation(corner_rotation[i]);
		}
				
		//	下の水
		AddGameObject<stage_wator_field>(LAYER_3D);

		//	大鳥居
		AddGameObject< stage_otorii>(LAYER_3D);
	}

};


