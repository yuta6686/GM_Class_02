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


void ShaderComponent::Init()
{
	m_VertexShader =
		ResourceManager<VertexShader>::GetResource(VertexShader::GetFileNames()[(SHADER_TYPE)m_ShaderType]);

	m_PixelShader = 
	ResourceManager<PixelShader>::GetResource(PixelShader::GetFileNames()[(SHADER_TYPE)m_ShaderType]);

	

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
