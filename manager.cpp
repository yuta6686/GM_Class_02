#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "polygon2D.h"
#include "field.h"
#include "player.h"
#include <list>
using namespace std;
list<GameObject*> g_3DGameObjects;
list<GameObject*> g_2DGameObjects;

Camera* Camera::m_Instance = 0;

Manager &Manager::Instance()
{	
	static Manager instance;
	return	instance;
}

void Manager::Init()
{
	Renderer::Init();
		
	g_2DGameObjects.push_back(new Polygon2D());

	g_3DGameObjects.push_back(Camera::Instance());
	g_3DGameObjects.push_back(new Field());
	g_3DGameObjects.push_back(new Player());

	
	for (auto x : g_2DGameObjects) 
		x->Init();	

	for (auto x : g_3DGameObjects) 
		x->Init();
	
}


void Manager::Uninit()
{
	Renderer::Uninit();

	for (auto x : g_2DGameObjects) {
		x->Uninit();
		delete x;
		x = nullptr;
	}


	for (auto x : g_3DGameObjects) {
		x->Uninit();
		delete x;
		x = nullptr;
	}

	
}

void Manager::Update()
{
	for (auto x : g_2DGameObjects) 
		x->Update();
	
	for (auto x : g_3DGameObjects) 
		x->Update();
	
}

void Manager::Draw()
{
	Renderer::Begin();

	//	æ‚É3D•`‰æ‚µ‚È‚¢‚Æ‚¢‚¯‚È‚¢‚ç‚µ‚¢B	
	Draw3D();

	Draw2D();
		

	Renderer::End();
}

void Manager::Draw2D()
{
	for (auto x : g_2DGameObjects) 
		x->Draw();	
}

void Manager::Draw3D()
{
	for (auto x : g_3DGameObjects) 
		x->Draw();
}
