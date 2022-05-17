#pragma once
#include "main.h"
#include "model.h"
#include "gameObject.h"

class Player:public GameObject
{
private:
	Model* m_Model;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
public:
	void Init()	 override;
	void Uninit()override;
	void Update()override;
	void Draw()	 override;
};

