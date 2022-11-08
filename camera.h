#pragma once
#include "main.h"
#include "gameobject.h"

class Camera : public GameObject
{
private:
	D3DXVECTOR3 m_Target;
	D3DXMATRIX	m_ViewMatrix;
	D3DXMATRIX	_projectionMatrix;

	float m_Length = 1.0f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }		
	bool CheckView(const D3DXVECTOR3& Position, const float& Scale);
};