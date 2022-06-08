#include "pixelShader.h"

void PixelShader::Draw()
{
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
}

void PixelShader::Load(const char* FileName)
{
	Renderer::CreatePixelShader(&m_PixelShader, FileName);
}

void PixelShader::Unload()
{
	m_PixelShader->Release();
}
