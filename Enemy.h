#pragma once
#include "main.h"
#include "model.h"
#include "gameobject.h"

class Enemy : public GameObject
{
private:
	Model* m_Model;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
