#include "texture.h"
#include "renderer.h"

void Texture::Draw()
{	
	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(_textureNum, 1, &m_Texture);

	if (_onlySet)return;

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Texture::Load(const char* FileName)
{
	//�e�N�X�`���ǂݍ���
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
