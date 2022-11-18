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
#include "rendering_texture.h"


void DebugScene::Init()
{
	AddGameObject<SwitchingRenderer>(LAYER_BEGIN)
		->SetLayerNum(LAYER_BEGIN);

	AddGameObject<SwitchingRenderer>(LAYER_TO_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_TO_RENDERING_TEXTURE);

	AddGameObject<RenderingTexture>(LAYER_RENDERING_TEXTURE);

	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	プレイヤー
	AddGameObject<Player>(LAYER_3D)->SetPosition({ 2.5f,5.0f,0.0f });

	//	メッシュフィールド
	AddGameObject<CO_MeshField>(LAYER_3D);

	AddGameObject<CO_UI_AimLing>(LAYER_2D);

	AddGameObject<UI_Charge>(LAYER_2D);

	AddGameObject<CO_AnimationModelTest>(LAYER_3D);

	AddGameObject<Prism>(LAYER_3D);

	float dest_y = 400.0f;
	float dep_y = 800.0f;
	{
		CO_UI_Quest_Belt* couibelt = AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
		couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y,0.0f });
		couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y,0.0f });
		couibelt->Start(false, 60, 60);
	}

	{
		float sep_y = 200.0f;
		CO_UI_Quest_Belt* couibelt = AddGameObject<CO_UI_Quest_Belt>(LAYER_2D);
		couibelt->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y + sep_y,0.0f });
		couibelt->SetDeparture({ -1920.0f / 1.5f,dep_y + sep_y,0.0f });
		couibelt->Start(false, 60, 90);
	}

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