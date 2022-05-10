#pragma once
#include "main.h"
#include "model.h"

class Player
{
private:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotateion;
	D3DXVECTOR3 m_Scale;

	Model* m_Model;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

