#include "texture.h"
#include "renderer.h"

void Texture::Draw()
{	
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(_textureNum, 1, &m_Texture);

	if (_onlySet)return;

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Texture::Load(const char* FileName)
{
	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		FileName,
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);		
}

void Texture::Unload()
{
	m_Texture->Release();
}
