#include "DebugScene.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "CO_MeshField.h"
#include "CO_UI_AimLing.h"
#include "UI_Charge.h"

void DebugScene::Init()
{
	//	�J����
	AddGameObject<Camera>(LAYER_FIRST);

	//	���C�g
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	�v���C���[
	AddGameObject<Player>(LAYER_3D)->SetPosition({ 2.5f,5.0f,0.0f });

	//	���b�V���t�B�[���h
	AddGameObject<CO_MeshField>(LAYER_3D);

	AddGameObject<CO_UI_AimLing>(LAYER_2D);

	AddGameObject<UI_Charge>(LAYER_2D);

	
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
		ImGui::MenuItem("MeshField", NULL, &mbGameObject);		

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();

	for (int i = 0; i < LAYER_NUM_MAX; i++) {

		for (GameObject* object : m_GameObject[i])
		{
			object->Draw();
#ifdef _DEBUG				
			object->DrawImgui();
			
#endif // _DEBUG
		}
	}

#ifdef _DEBUG
	ImGui::End();

	ImGui::PopStyleColor();
#endif // _DEBUG
}