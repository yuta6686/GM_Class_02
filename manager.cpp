#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GameScene.h"


Scene* Manager::m_Scene;

//‰Šú‰»ˆ—
void Manager::Init()
{
	Renderer::Init();


	m_Scene = new GameScene();
	m_Scene->Init();
}

//I—¹ˆ—
void Manager::Uninit()
{
	m_Scene->UnInit();
	delete m_Scene;

	Renderer::Uninit();
}


//XVˆ—
void Manager::Update()
{
	m_Scene->Update();
}


//•`‰æˆ—
void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();
}

