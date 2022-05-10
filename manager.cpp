#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"
#include "player.h"


Polygon2D* g_polygon = nullptr;
Field* g_field = nullptr;
Camera* g_camera = nullptr;
Player* g_player = nullptr;

void Manager::Init()
{
	Renderer::Init();	
	
	g_polygon = new Polygon2D();
	g_field = new Field();
	g_camera = new Camera();
	g_player = new Player();

	g_polygon->Init();
	g_field->Init();
	g_camera->Init();
	g_player->Init();
}


void Manager::Uninit()
{
	Renderer::Uninit();

	g_polygon->Uninit();
	g_field->Uninit();
	g_camera->Uninit();
	g_player->Uninit();

	delete g_polygon;
	delete g_field;
	delete g_camera;
	delete g_player;
}

void Manager::Update()
{
	g_camera->Update();
	g_polygon->Update();
	g_field->Update();
	g_player->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	//	Camera
	g_camera->Draw();

	//	æ‚É3D•`‰æ‚µ‚È‚¢‚Æ‚¢‚¯‚È‚¢‚ç‚µ‚¢B

	//	3D
	g_field->Draw();	
	g_player->Draw();


	//	2D
	g_polygon->Draw();
	

	Renderer::End();
}
