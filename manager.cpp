

#include "renderer.h"
#include "game_scene.h"
#include "title_scene.h"
#include "result_scene.h"
#include "audio.h"
#include "GameObject_Invoke.h"
#include "animation_model.h"
#include "debug_scene.h"
#include "rendering_texture.h"

//Scene* Manager::m_Scene;
std::shared_ptr<Scene> Manager::m_Scene=nullptr;

//初期化処理
void Manager::Init()
{
	Renderer::Init();

	Audio::InitMaster();

	m_Scene = std::make_shared<DebugScene>();
	m_Scene->Init();
	
	

	//m_Scene = new ResultScene();
	//m_Scene->Init();
}

//終了処理
void Manager::Uninit()
{
	m_Scene->UnInit();

	/*m_Scene->UnInit();
	delete m_Scene;*/

	ResourceManger<Model>::AllRelease();
	ResourceManger<Model_variable>::AllRelease();
	ResourceManger<Texture>::AllRelease();
	ResourceManger<VertexShader>::AllRelease();
	ResourceManger<PixelShader>::AllRelease();
	ResourceManger<AnimationModel>::AllRelease();

	Audio::UninitMaster();

	Renderer::Uninit();
}


//更新処理
void Manager::Update()
{
	m_Scene->Update();
	

	//m_Scene->Update();
}


//描画処理
void Manager::Draw()
{
	//Renderer::BeginDef();

	m_Scene->Draw();

	//Renderer::EndDef();

	//Renderer::Begin();	

	// m_Scene->Draw();	


	

	Renderer::End();
}

