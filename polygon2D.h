#pragma once

#include"gameObject.h"
#include "texture.h"
class Polygon2D:public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	//ID3D11ShaderResourceView*	m_Texture = NULL;
	std::shared_ptr<Resource> m_Texture;

	ID3D11VertexShader*			m_VertexShader=nullptr;
	ID3D11PixelShader*			m_PixelShader=nullptr;
	ID3D11InputLayout*			m_VertexLayout=nullptr;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

