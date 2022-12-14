#include "stdafx.h"

void Scene::Unload()
{
	ResourceManger<Model>::AllRelease();
	ResourceManger<Texture>::AllRelease();
	ResourceManger<VertexShader>::AllRelease();
	ResourceManger<PixelShader>::AllRelease();
}

GameObject* Scene::AddGameObject(GameObject* pGameObject, int layer)
{
	pGameObject->Init();
	m_GameObject[layer].push_back(pGameObject);
	return pGameObject;
}

std::vector<GameObject*> Scene::GetGameObjectLayer(const int& Layer)
{
	std::vector<GameObject*> objects;
	for (auto obj : m_GameObject[Layer]) {
		objects.push_back(obj);
	}
	return objects;
}
void Scene::UnInit()
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

void Scene::Update()
{
	for (int i = 0; i < LAYER_NUM_MAX; i++) {
		for (GameObject* object : m_GameObject[i])
		{

			object->Update();

		}

		m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
	}
}

void Scene::Draw()
{
#ifdef _DEBUG
	ImGui::PushStyleColor(ImGuiCol_WindowBg, MyImgui::window_color);

	if (MyImgui::_myFlag["showDemoWindow"])
		ImGui::ShowDemoWindow();

	ImGui::Begin("Parameters by Scene", &parameters_by_scene, ImGuiWindowFlags_MenuBar);

	//	メニューバー
	ImGui::BeginMenuBar(); {

		// mainに入れる方
		static bool mainflag = false;
		if (ImGui::BeginMenu("main")) {

			for (auto& my : MyImgui::_myFlag) {
				ImGui::MenuItem(my.first.c_str(), NULL, &my.second);
			}

			ImGui::EndMenu();
		}

		// main以外のMenu群
		for (auto& menu : MyImgui::_myFlagTree) {
			if (ImGui::BeginMenu(menu.first.c_str()))
			{

				for (auto& menu_item : menu.second) {
					ImGui::MenuItem(menu_item.first.c_str(), NULL, &menu_item.second);
				}

				ImGui::EndMenu();
			}
		}

		//	メニューバー終了
		ImGui::EndMenuBar();
	}


#endif // _DEBUG


	for (int i = 0; i < LAYER_NUM_MAX; i++) {

		for (GameObject* object : m_GameObject[i])
		{
			object->Draw();
#ifdef _DEBUG
			ImGuiComponent* imc = object->GetComponent<ImGuiComponent>();
			if (imc == nullptr)continue;
			if (imc->GetIsUse() == false)continue;
			object->DrawImgui();
#endif // _DEBUG
		}
	}


#ifdef _DEBUG
	MyImgui::MyImguiDraw();

	ImGui::End();

	ImGui::PopStyleColor();
#endif // _DEBUG

}
