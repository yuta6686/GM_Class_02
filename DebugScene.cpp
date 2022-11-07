#include "DebugScene.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "CO_MeshField.h"
#include "CO_UI_AimLing.h"
#include "UI_Charge.h"
#include "MyImgui.h"
#include "CO_AnimationModelTest.h"
#include "ComputeShaderTestObject.h"

void DebugScene::SetParticle()
{
	PARTICLE par;
	par.acc = { 0.0f,0.0f,0.0f };
	par.m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
	par.m_ColorOverLifeTime_End = { 0.0f,0.0f,0.0f,1.0f };
	par.col = par.m_ColorOverLifeTime_Start;
	par.life = 60;
	par.pos = _player->GetPosition() + MyMath::XZRandom(-3.0f, 3.0f);
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel = MyMath::VEC3Random(-0.01f, 0.01f);
	par.m_SizeOverLifeTime_Start = MyMath::Random(0.05f, 0.1f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.status = 0;
	par.type = rand() % PARTICLE_TYPE_MAX;
	par.use = true;
	par.use_torii = false;
	par.vel = MyMath::XZRandom(-0.15f, 0.15f);
	par.vel.y = MyMath::Random(0.01f, 0.05f);
	_particleObject->SetParticle(par);

}

void DebugScene::Init()
{
	//	カメラ
	AddGameObject<Camera>(LAYER_FIRST);

	//	ライト
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	// パーティクル
	_particleObject = AddGameObject<ParticleObject>(LAYER_3D);

	//	プレイヤー
	_player = AddGameObject<Player>(LAYER_3D);
	_player->SetPosition({ 2.5f,5.0f,0.0f });

	//	メッシュフィールド
	AddGameObject<CO_MeshField>(LAYER_3D);

	AddGameObject<CO_UI_AimLing>(LAYER_2D);

	AddGameObject<UI_Charge>(LAYER_2D);

	AddGameObject<CO_AnimationModelTest>(LAYER_3D);

	//AddGameObject<ComputeShaderTestObject>(LAYER_3D);

	for (int i = 0; i < LAYER_NUM_MAX; i++) {

		for (GameObject* object : m_GameObject[i])
		{
			MyImgui::mbGameObjectMap[object->GetTypeName()] = false;
		}
	}	

	MyImgui::mbGameObjectMap["MeshField"] = true;
}

void DebugScene::Update()
{
	for(int i=0;i<_particle1FrameNum;i++)
		SetParticle();

	Scene::Update();
}
void DebugScene::Draw()
{
#ifdef _DEBUG
	ImGui::PushStyleColor(ImGuiCol_WindowBg, Renderer::GetWindowColor());

	ImGui::Begin("Debug Scene", &parameters_by_scene, ImGuiWindowFlags_MenuBar);
#endif // _DEBUG

	ImGui::BeginMenuBar();

	ImGui::SliderInt("Particle 1Frame Num", &_particle1FrameNum, 0, 30, "%d");

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