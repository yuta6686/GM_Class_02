#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "audio.h"
#include "GameObject_Invoke.h"


//Scene* Manager::m_Scene;
std::shared_ptr<Scene> Manager::m_Scene=nullptr;

//初期化処理
void Manager::Init()
{
	Renderer::Init();

	Audio::InitMaster();

	m_Scene = std::make_shared<TitleScene>();
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
	Renderer::Begin();

	//	m_Scene->Draw();

	m_Scene->Draw();

#ifdef _DEBUG
	Renderer::imguiDraw();
#endif // _DEBUG

	

	Renderer::End();
}

