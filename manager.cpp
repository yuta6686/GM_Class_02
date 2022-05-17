#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

Scene* Manager::m_pScene=nullptr;

Manager &Manager::Instance()
{	
	static Manager instance;
	return	instance;
}

void Manager::Init()
{
	Renderer::Init();
		
	m_pScene = new Scene();
	m_pScene->Init();
	
}


void Manager::Uninit()
{
	Renderer::Uninit();	

	m_pScene->Uninit();
}

void Manager::Update()
{
	m_pScene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_pScene->Draw();
		

	Renderer::End();
}


