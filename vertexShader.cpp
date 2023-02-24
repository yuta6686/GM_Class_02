#include "vertexShader.h"

void VertexShader::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout.Get());

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader.Get(), NULL, 0);
}

void VertexShader::Load(const char* FileName)
{
	std::string fileName;
	fileName = SHADER_PASS + FileName;
	Renderer::CreateVertexShader(m_VertexShader.GetAddressOf(), m_VertexLayout.GetAddressOf(),
		fileName.c_str());
}

void VertexShader::Unload()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();	
}
