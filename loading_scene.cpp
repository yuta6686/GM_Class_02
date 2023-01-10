#include "stdafx.h"
#include "loading_scene.h"
#include "game_scene.h"
#include "particle_object_2d.h"
#include "switching_renderer.h"

void Loading::Init()
{
	AddGameObject<SwitchinRendererFactory>(LAYER_BEGIN);

	_particle = AddGameObject<ParticleObject_2D>(LAYER_2D);

	std::thread th(GameScene::Load);
	th.detach();	
}

void Loading::UnInit()
{
	Scene::UnInit();
}

void Loading::Update()
{
	_particle->SetParticle_Rising();

	Scene::Update();

	if (GameScene::GetLoadFinish()) 
	{		
		Manager::SetScene<GameScene>();
	}
}
