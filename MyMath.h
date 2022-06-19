#pragma once
#include "main.h"
class MyMath
{
public:
	static float GetRadian(float degree) { return degree * (D3DX_PI / 180.0f); }
	static D3DXVECTOR3 GetRadian(D3DXVECTOR3 degree) { return degree * (D3DX_PI / 180.0f); }
	static D3DXVECTOR3 GetDegree(D3DXVECTOR3 radian) { return radian * (180.0f / D3DX_PI); }
};

