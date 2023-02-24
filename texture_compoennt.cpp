#include "stdafx.h"
#include "texture_compoennt.h"




void TextureComponent::Init()
{
	
}

void TextureComponent::Uninit()
{
	
}

void TextureComponent::Update()
{
}

void TextureComponent::Draw()
{
	_texture->Draw();
}

void TextureComponent::DrawImgui()
{
}

void TextureComponent::SetTextureAndSlot(const std::string& fileName, const int& texSlot,const bool& flag)
{
	_fileName = fileName;
	_texture = ResourceManager<Texture>::GetResource(fileName);
	_texture->SetTextureNum(texSlot,flag);
}


std::string TextureComponent::GetFileName() const
{
	return _fileName;
}
