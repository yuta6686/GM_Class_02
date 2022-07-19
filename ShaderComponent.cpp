#include "ShaderComponent.h"
#include "ResourceManager.h"

void ShaderComponent::Init()
{
	switch (m_ShaderType)
	{
	case SHADER_DEFAULT:
		m_VertexShader =
			ResourceManger<VertexShader>::GetResource(VertexShader::DEFAULT_VERTEX_SHADER.c_str());
		m_PixelShader =
			ResourceManger<PixelShader>::GetResource(PixelShader::DEFAULT_PIXEL_SHADER.c_str());
		break;
	case SHADER_UNLIT:
		m_VertexShader =
			ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
		m_PixelShader =
			ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());
		break;
	default:
		break;
	}
	

}

void ShaderComponent::Uninit()
{
}

void ShaderComponent::Update()
{
}

void ShaderComponent::Draw()
{
	m_VertexShader->Draw();
	m_PixelShader->Draw();
}
