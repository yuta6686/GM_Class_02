#pragma once
#include "gameObject.h"

class Camera :public GameObject
{
private :
	D3DXVECTOR3 m_Target;

public:
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
};

