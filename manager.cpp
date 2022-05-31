
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

static class Scene* m_Scene;

Manager &Manager::Instance()
{	
	static Manager instance;
	return	instance;
}

void Manager::Init()
{
	Renderer::Init();
		
	m_Scene->Init();
	
}


void Manager::Uninit()
{
	Renderer::Uninit();	

	m_Scene->Uninit();

	
}

void Manager::Update()
{
	m_Scene->Update();
	
}

void Manager::Draw()
{
	Renderer::Begin();

	//	���3D�`�悵�Ȃ��Ƃ����Ȃ��炵���B	
	/*Draw3D();

	Draw2D();*/
	m_Scene->Draw();
		

	Renderer::End();
}

void Manager::Draw2D()
{

}

void Manager::Draw3D()
{

}
