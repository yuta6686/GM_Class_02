#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"


Scene* Manager::m_Scene;

//初期化処理
void Manager::Init()
{
	Renderer::Init();


	m_Scene = new Scene();
	m_Scene->Init();
}

//終了処理
void Manager::Uninit()
{
	m_Scene->UnInit();
	delete m_Scene;

	Renderer::Uninit();
}


//更新処理
void Manager::Update()
{
	m_Scene->Update();
}


//描画処理
void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();
}

