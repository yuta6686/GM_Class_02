#include "stdafx.h"

void Scene::Unload()
{
	ResourceManger<Model>::AllRelease();
	ResourceManger<Texture>::AllRelease();
	ResourceManger<Model_variable>::AllRelease();
	ResourceManger<AnimationModel>::AllRelease();
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
void Scene::DefaultImGuiDraw()
{
	ImGui::Text("Framerate : %.1f FPS", ImGui::GetIO().Framerate);
	{
		ImGui::SameLine();
		ImGui::ProgressBar(ImGui::GetIO().Framerate / 60.0f);

		{
			static float value[180];
			for (int i = 0; i < 179; i++)
				value[i] = value[i + 1];

			value[179] = ImGui::GetIO().Framerate;

			ImGui::PlotLines("", value, sizeof(value) / sizeof(float),
				0, nullptr, 0.f, 100.f, ImVec2(0, 50));
		}

		{
			LARGE_INTEGER qpf;
			LARGE_INTEGER qpc;

			QueryPerformanceFrequency(&qpf);
			QueryPerformanceCounter(&qpc);

			static float value[180];
			for (int i = 0; i < 179; i++)
				value[i] = value[i + 1];

			LONGLONG time = qpc.QuadPart;
			static LONGLONG lastTime;

			float drawTime = (time - lastTime) * 1000.0f / qpf.QuadPart;
			lastTime = time;

			value[179] = drawTime;

			ImGui::PlotLines("", value, sizeof(value) / sizeof(float),
				0, nullptr, 0.f, 100.f, ImVec2(0, 50));

		}
	}

	ImGui::Text("MousePosDiffX: %d \nMousePosDiffY: %d", GetMouseX(), GetMouseY());

	ImGui::Text("Mouse_X: %.f", ImGui::GetIO().MousePos.x);
	ImGui::SameLine();
	ImGui::ProgressBar(ImGui::GetIO().MousePos.x / SCREEN_WIDTH);

	ImGui::Text("Mouse_Y: %.f", ImGui::GetIO().MousePos.y);
	ImGui::SameLine();
	ImGui::ProgressBar(ImGui::GetIO().MousePos.y / SCREEN_HEIGHT);

	

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

	ImGui::Begin("Parameters by Scene", &parameters_by_scene, 
		ImGuiWindowFlags_MenuBar | 
		ImGuiWindowFlags_AlwaysAutoResize);

	DefaultImGuiDraw();

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
