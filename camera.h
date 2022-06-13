#pragma once
#include "main.h"
#include "gameobject.h"

class Camera : public GameObject
{
private:
	D3DXVECTOR3 m_Target;
	D3DXMATRIX	m_ViewMatrix;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }	
};