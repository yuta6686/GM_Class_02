#include "DebugScene.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "CO_MeshField.h"
#include "CO_UI_AimLing.h"
#include "UI_Charge.h"
#include "MyImgui.h"
#include "CO_AnimationModelTest.h"
#include "Prism.h"
#include "UI_Score.h"


void DebugScene::Init()
{
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