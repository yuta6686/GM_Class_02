#pragma once
#include "main.h"
#include "gameobject.h"

class Camera : public GameObject
{
private:
	D3DXVECTOR3 m_Target;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};