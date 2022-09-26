#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "audio.h"
#include "GameObject_Invoke.h"
#include "AnimationModel.h"
#include "DebugScene.h"

//Scene* Manager::m_Scene;
std::shared_ptr<Scene> Manager::m_Scene=nullptr;

//‰Šú‰»ˆ—
void Manager::Init()
{
	Renderer::Init();

	Audio::InitMaster();

	m_Scene = std::make_shared<DebugScene>();
	m_Scene->Init();
	
	//m_Scene = new ResultScene();
	//m_Scene->Init();
}

//I—¹ˆ—
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


//XVˆ—
void Manager::Update()
{
	m_Scene->Update();

	

	//m_Scene->Update();
}


//•`‰æˆ—
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

