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
		m_GameObject[i].clear();//���X�g�̃N���A
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

	//	���j���[�o�[
	ImGui::BeginMenuBar(); {

		static bool mainflag = false;
		if (ImGui::BeginMenu("main")) {

			for (auto& my : MyImgui::_myFlag) {
				ImGui::MenuItem(my.first.c_str(), NULL, &my.second);
			}

			ImGui::EndMenu();
		}

		//	���j���[�o�[�I��
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
	ImGui::End();

	ImGui::PopStyleColor();
#endif // _DEBUG

}
