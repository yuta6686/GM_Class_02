#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"

Polygon2D* g_polygon = nullptr;
Field* g_field = nullptr;
Camera* g_camera = nullptr;

void Manager::Init()
{
	Renderer::Init();	
	
	g_polygon = new Polygon2D();
	g_field = new Field();
	g_camera = new Camera();

	g_polygon->Init();
	g_field->Init();
	g_camera->Init();
}


void Manager::Uninit()
{
	Renderer::Uninit();

	g_polygon->Uninit();
	g_field->Uninit();
	g_camera->Uninit();

	delete g_polygon;
	delete g_field;
	delete g_camera;
}

void Manager::Update()
{
	g_camera->Update();
	g_polygon->Update();
	g_field->Update();
	
}

void Manager::Draw()
{
	Renderer::Begin();

	g_camera->Draw();
	g_field->Draw();
	g_polygon->Draw();
	
	

	Renderer::End();
}
