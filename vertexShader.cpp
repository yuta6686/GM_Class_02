#include "vertexShader.h"

void VertexShader::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
}

void VertexShader::Load(const char* FileName)
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		FileName);
}

void VertexShader::Unload()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();	
}
