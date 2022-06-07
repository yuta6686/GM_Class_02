#pragma once
#include <map>
#include <string>
#include <memory>
#include "main.h"
#include "renderer.h"
#include"Texture.h"

class TextureFactory
{
private:
	//	�摜���v�[������R���e�i (K,V) = ( fileName,Texture);
	std::map<std::string, std::shared_ptr<Texture>> textureContainer;

	//	�摜�N���X���쐬
	std::shared_ptr<Texture> createTexture(std::string fileName) 
	{
		ID3D11ShaderResourceView* handle;

		D3DX11CreateShaderResourceViewFromFileA(Renderer::GetDevice(),
			fileName.c_str(),
			NULL,
			NULL,
			&handle,
			NULL);
	}
};

