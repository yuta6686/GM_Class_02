#pragma once
#include "main.h"
#include"gameObject.h"
class Polygon2D:public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			m_VertexLayout;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

