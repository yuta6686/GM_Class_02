#pragma once
#include "gameObject.h"
#include "texture.h"

class Field:public GameObject
{
private:
	float m_pos;

	ID3D11Buffer* m_VertexBuffer = NULL;
	std::shared_ptr<Resource> m_Texture;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
public:
	void Init()		override ;
	void Uninit()	override ;
	void Update()	override ;
	void Draw()		override ;
};

