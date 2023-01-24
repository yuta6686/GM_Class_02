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
	// RenderingTexture����̐����Ƃ܂Ƃ� https://yuta6686.atlassian.net/browse/AS-40
	switch (_layerNum)
	{
	case LAYER_BEGIN:
		Renderer::BeginOfScr();
		break;
	case LAYER_LUMINANCE:
		
		break;
	case LAYER_BLUR_X:
		
		break;
	case LAYER_BLUR_Y:
		
		break;
	case LAYER_COPY:
		
		break;

	default:
		break;
	}
}

void SwitchinRendererFactory::Create()
{
	_scene->AddGameObject<SwitchingRenderer>(LAYER_BEGIN)
		->SetLayerNum(LAYER_BEGIN);
	

	_scene->AddGameObject<RenderingTexture>(LAYER_TO_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_TO_RENDERING_TEXTURE);

	// https://yuta6686.atlassian.net/browse/AS-41 �P�x���o�p
	_scene->AddGameObject<RenderingTexture>(LAYER_LUMINANCE)
		->SetLayerNum(LAYER_LUMINANCE);

	_scene->AddGameObject<RenderingTexture>(LAYER_BLUR_X)
		->SetLayerNum(LAYER_BLUR_X);

	_scene->AddGameObject<RenderingTexture>(LAYER_BLUR_Y)
		->SetLayerNum(LAYER_BLUR_Y);

	_scene->AddGameObject<RenderingTexture>(LAYER_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_RENDERING_TEXTURE);

	_scene->AddGameObject<RenderingTexture>(LAYER_COPY)
		->SetLayerNum(LAYER_COPY);

	_scene->AddGameObject<RenderingTexture>(LAYER_BLOOM)
		->SetLayerNum(LAYER_BLOOM);
}
