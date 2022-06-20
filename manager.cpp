#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "GameScene.h"


Scene* Manager::m_Scene;

//����������
void Manager::Init()
{
	Renderer::Init();


	m_Scene = new GameScene();
	m_Scene->Init();
}

//�I������
void Manager::Uninit()
{
	m_Scene->UnInit();
	delete m_Scene;

	Renderer::Uninit();
}


//�X�V����
void Manager::Update()
{
	m_Scene->Update();
}


//�`�揈��
void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();

	Renderer::End();
}

