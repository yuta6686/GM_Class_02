#include "debug_scene.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "co_mesh_field.h"
#include "co_ui_aimling.h"
#include "ui_charge.h"
#include "my_imgui.h"
#include "co_animation_model_test.h"
#include "prism.h"
#include "ui_score.h"

#include "co_ui_quest_belt.h"
#include "switching_renderer.h"

// factory
#include "ui_factory.h"
#include "player_factory.h"

void DebugScene::Init()
{
	AddGameObject<SwitchinRendererFactory>(LAYER_BEGIN);

	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	プレイヤー
	AddGameObject<PlayerFactory>(LAYER_3D);

	//	メッシュフィールド
	AddGameObject<CO_MeshField>(LAYER_3D);

	//AddGameObject<CO_AnimationModelTest>(LAYER_3D);

	AddGameObject<Prism>(LAYER_3D);

	

	AddGameObject<UIFactory>(LAYER_2D);

	for (int i = 0; i < LAYER_NUM_MAX; i++) {

		for (GameObject* object : m_GameObject[i])
		{
			MyImgui::mbGameObjectMap[object->GetTypeName()] = false;
		}
	}	

	MyImgui::mbGameObjectMap["MeshField"] = true;
}

//void DebugScene::Update()
//{
//
//
//	Scene::Update();
//}
void DebugScene::Draw()
{
#ifdef _DEBUG
	ImGui::PushStyleColor(ImGuiCol_WindowBg, Renderer::GetWindowColor());

	ImGui::Begin("Debug Scene", &parameters_by_scene, ImGuiWindowFlags_MenuBar);
#endif // _DEBUG

	ImGui::BeginMenuBar();

	

	if (ImGui::BeginMenu("GameObject"))
	{
		for (auto gomap : MyImgui::mbGameObjectMap) {
			ImGui::MenuItem(gomap.first.c_str(),NULL, &MyImgui::mbGameObjectMap[gomap.first]);			
		}

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();

	for (int i = 0; i < LAYER_NUM_MAX; i++) {

		for (GameObject* object : m_GameObject[i])
		{
			object->Draw();
#ifdef _DEBUG
			
			if(MyImgui::mbGameObjectMap[object->GetTypeName()])
				object->DrawImgui();					
#endif // _DEBUG
		}
	}

#ifdef _DEBUG
	ImGui::End();

	ImGui::PopStyleColor();
#endif // _DEBUG
}