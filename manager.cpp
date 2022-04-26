#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "field.h"

Polygon2D* g_polygon = nullptr;
Field* g_field = nullptr;


void Manager::Init()
{
	Renderer::Init();	
	
	g_polygon = new Polygon2D();
	g_field = new Field();

	g_polygon->Init();
	g_field->Init();
}


void Manager::Uninit()
{
	Renderer::Uninit();

	g_polygon->Uninit();
	g_field->Uninit();

	delete g_polygon;
	delete g_field;
}

void Manager::Update()
{
	g_polygon->Update();
	g_field->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_polygon->Draw();
	g_field->Draw();


	Renderer::End();
}
