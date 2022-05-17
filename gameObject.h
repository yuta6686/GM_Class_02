#pragma once
#include "main.h"
class GameObject
{
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotateion;
	D3DXVECTOR3 m_Scale;
public:
	virtual void Init()	 = 0;
	virtual void Uninit()= 0;
	virtual void Update()= 0;
	virtual void Draw()	 = 0;
};

