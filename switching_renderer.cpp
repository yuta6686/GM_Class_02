#include "switching_renderer.h"
#include "rendering_texture.h"

void SwitchingRenderer::Init()
{
}

void SwitchingRenderer::Uninit()
{
}

void SwitchingRenderer::Update()
{
}

void SwitchingRenderer::Draw()
{
	switch (_layerNum)
	{
	case LAYER_BEGIN:
		Renderer::BeginOfScr();		
		break;
	case LAYER_TO_RENDERING_TEXTURE:
		Renderer::Begin();
		break;
	default:
		break;
	}
}

void SwitchinRendererFactory::Create()
{
	_scene->AddGameObject<SwitchingRenderer>(LAYER_BEGIN)
		->SetLayerNum(LAYER_BEGIN);

	_scene->AddGameObject<SwitchingRenderer>(LAYER_TO_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_TO_RENDERING_TEXTURE);

	_scene->AddGameObject<RenderingTexture>(LAYER_RENDERING_TEXTURE);
}
