#include "pixelShader.h"

void PixelShader::Draw()
{
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader.Get(), NULL, 0);
}

void PixelShader::Load(const char* FileName)
{
	Renderer::CreatePixelShader(m_PixelShader.GetAddressOf(), FileName);
	assert(m_PixelShader);
}

void PixelShader::Unload()
{
	m_PixelShader->Release();
}
