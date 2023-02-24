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
	// RenderingTextureŽü‚è‚Ì®—‚Æ‚Ü‚Æ‚ß https://yuta6686.atlassian.net/browse/AS-40
	switch (_layerNum)
	{
	case LAYER_BEGIN:
		Renderer::BeginOfScr();
		break;
	case LAYER_LUMINANCE:
		
		break;

	default:
		break;
	}
}

void SwitchinRendererFactory::Create()
{
	_scene->AddGameObject<RenderingTexture>(LAYER_BEGIN)
		->SetLayerNum(LAYER_BEGIN);
	

	_scene->AddGameObject<RenderingTexture>(LAYER_TO_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_TO_RENDERING_TEXTURE);

	// https://yuta6686.atlassian.net/browse/AS-41 ‹P“x’Šo—p
	_scene->AddGameObject<RenderingTexture>(LAYER_LUMINANCE)
		->SetLayerNum(LAYER_LUMINANCE);

	_scene->AddGameObject<RenderingTexture>(LAYER_BLUR)
		->SetLayerNum(LAYER_BLUR);

	/*_scene->AddGameObject<RenderingTexture>(LAYER_BLUR_Y)
		->SetLayerNum(LAYER_BLUR_Y);*/

	_scene->AddGameObject<RenderingTexture>(LAYER_RENDERING_TEXTURE)
		->SetLayerNum(LAYER_RENDERING_TEXTURE);


	_scene->AddGameObject<RenderingTexture>(LAYER_BLOOM)
		->SetLayerNum(LAYER_BLOOM);
}
