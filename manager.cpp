#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"

Polygon2D* g_polygon = nullptr;



void Manager::Init()
{
	Renderer::Init();	
	
	g_polygon = new Polygon2D();

	g_polygon->Init();
}


void Manager::Uninit()
{
	Renderer::Uninit();

	g_polygon->Uninit();

	delete g_polygon;
}

void Manager::Update()
{
	g_polygon->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_polygon->Draw();


	Renderer::End();
}
