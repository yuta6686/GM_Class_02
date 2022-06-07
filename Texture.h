#pragma once
#include "main.h"
#include "Texture.h"
class Texture
{
private:
	ID3D11ShaderResourceView* m_handle;
public:
	Texture(ID3D11ShaderResourceView* handle) {
		this->m_handle = handle;		
	}

	ID3D11ShaderResourceView* GetTexture() { return m_handle; }
};

	