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
	//	画像をプールするコンテナ (K,V) = ( fileName,Texture);
	std::map<std::string, std::shared_ptr<Texture>> textureContainer;

	//	画像クラスを作成
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

