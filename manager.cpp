#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"


//Scene* Manager::m_Scene;
std::shared_ptr<Scene> Manager::sh_Scene;

//‰Šú‰»ˆ—
void Manager::Init()
{
	Renderer::Init();

	sh_Scene = std::make_shared<ResultScene>();
	sh_Scene->Init();

	//m_Scene = new ResultScene();
	//m_Scene->Init();
}

//I—¹ˆ—
void Manager::Uninit()
{
	sh_Scene->UnInit();

	/*m_Scene->UnInit();
	delete m_Scene;*/

	Renderer::Uninit();
}


//XVˆ—
void Manager::Update()
{
	sh_Scene->Update();

	//m_Scene->Update();
}


//•`‰æˆ—
void Manager::Draw()
{
	Renderer::Begin();

	sh_Scene->Draw();

	//m_Scene->Draw();

	Renderer::End();
}

