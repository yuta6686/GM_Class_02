#pragma once
#include "main.h"
#include "gameobject.h"

class Bullet : public GameObject
{
private:
	static inline const float BULLET_SPEED_MAX = 1.0f;
	static inline std::shared_ptr<Resource> m_Model;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

public:
	
	

	void Init();
	void Uninit();
	void Update();
	void Draw();

};

