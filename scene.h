#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include <string>


#include "resource_manager.h"
#include "gameObject.h"
#include "imgui_component.h"

enum LAYER {
	LAYER_BEGIN = 0,
	LAYER_FIRST,
	LAYER_3D,
	LAYER_AUDIO,
	LAYER_ENEMY,
	LAYER_TO_RENDERING_TEXTURE,
	LAYER_RENDERING_TEXTURE,
	LAYER_2D,
	LAYER_PARTICLE,	
	LAYER_NUM_MAX,
};


class Scene
{
protected:
	std::list<GameObject*> m_GameObject[LAYER_NUM_MAX];
	std::map<std::string, bool> m_Container;
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
	GameObject* AddGameObject(GameObject* pGameObject, int layer)
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

	std::vector<GameObject*> GetGameObjectLayer(const int& Layer)
	{
		std::vector<GameObject*> objects;
		for (auto obj : m_GameObject[Layer]) {
			objects.push_back(obj);
		}		
		return objects;
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
#ifdef _DEBUG
		ImGui::PushStyleColor(ImGuiCol_WindowBg, Renderer::GetWindowColor());

		ImGui::Begin("Parameters by Scene", &parameters_by_scene, ImGuiWindowFlags_MenuBar);
#endif // _DEBUG


		for (int i = 0; i < LAYER_NUM_MAX; i++) {					

			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
#ifdef _DEBUG
				ImGuiComponent* imc = object->GetComponent<ImGuiComponent>();
				if (imc == nullptr)continue;
				if (imc->GetIsUse() == false)continue;
				if (ImGui::CollapsingHeader(object->GetTypeName().c_str())) {
					object->DrawImgui();
				}				
#endif // _DEBUG
			}			
		}

#ifdef _DEBUG
		ImGui::End();

		ImGui::PopStyleColor();
#endif // _DEBUG

	}

	inline static bool parameters_by_scene = true;
private:



};


