#include "SwitchingRenderer.h"
#include "scene.h"

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
