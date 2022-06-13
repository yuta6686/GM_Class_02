#pragma once
#include "main.h"
#include "Resource.h"
#include "Enemy_Interface.h"

class Enemy : public Enemy_Interface
{
protected:
	static inline std::shared_ptr<Model> m_Model;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

public:
	static void Load();
	static void Unload();
	void Init();
	void Uninit();
	void Update();
	void Draw();

		
};
