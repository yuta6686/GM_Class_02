//  ---------------------------------------------------------
//  ShaderComponent [ShaderComponent.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - �V�F�[�_�p�R���|�[�l���g
// 
//	- ShaderType�ŕς��
//  ---------------------------------------------------------

#include "ShaderComponent.h"
#include "ResourceManager.h"

void ShaderComponent::Init()
{
	switch (m_ShaderType)
	{
	case SHADER_DEFAULT:
		m_VertexShader =
			ResourceManager<VertexShader>::GetResource(VertexShader::DEFAULT_VERTEX_SHADER.c_str());
		m_PixelShader =
			ResourceManager<PixelShader>::GetResource(PixelShader::DEFAULT_PIXEL_SHADER.c_str());
		break;
	case SHADER_UNLIT:
		m_VertexShader =
			ResourceManager<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
		m_PixelShader =
			ResourceManager<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());
		break;
	case SHADER_UNLIT_NO_MATERIAL:
		m_VertexShader =
			ResourceManager<VertexShader>::GetResource(VertexShader::UNLIT_NO_MATERIAL_VERTEX_SHADER.c_str());
		m_PixelShader =
			ResourceManager<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());
		break;
	case SHADER_TEST:
		m_VertexShader =
			ResourceManager<VertexShader>::GetResource("testVS.cso");
		m_PixelShader =
			ResourceManager<PixelShader>::GetResource("testPS.cso");
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
