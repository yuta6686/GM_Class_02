#include "pixelShader.h"

void PixelShader::Draw()
{
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader.Get(), NULL, 0);
}

void PixelShader::Load(const char* FileName)
{
	std::string fileName;
	fileName = SHADER_PASS + FileName;
	Renderer::CreatePixelShader(m_PixelShader.GetAddressOf(), fileName.c_str());
	assert(m_PixelShader);
}

void PixelShader::Unload()
{
	m_PixelShader->Release();
}
