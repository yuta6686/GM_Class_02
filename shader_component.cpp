//  ---------------------------------------------------------
//  ShaderComponent [ShaderComponent.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - シェーダ用コンポーネント
// 
//	- ShaderTypeで変わる
//  ---------------------------------------------------------

#include "shader_component.h"
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
	case SHADER_UNLIT_NO_MATERIAL:
		m_VertexShader =
			ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_NO_MATERIAL_VERTEX_SHADER.c_str());
		m_PixelShader =
			ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());
		break;
	case SHADER_TEST:
		m_VertexShader =
			ResourceManger<VertexShader>::GetResource("testVS.cso");
		m_PixelShader =
			ResourceManger<PixelShader>::GetResource("testPS.cso");
		break;
	case SHADER_RENDERING_TEXTURE:
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
