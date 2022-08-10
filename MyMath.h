#pragma once
#include "main.h"
#include "renderer.h"
class MyMath
{
public:
	static float GetRadian(float degree) { return degree * (D3DX_PI / 180.0f); }
	static D3DXVECTOR3 GetRadian(D3DXVECTOR3 degree) { return degree * (D3DX_PI / 180.0f); }
	static float GetDegree(float radian) { return radian * (180.0f / D3DX_PI); }
	static D3DXVECTOR3 GetDegree(D3DXVECTOR3 radian) { return radian * (180.0f / D3DX_PI); }
	static float GetViewAngle(D3DXVECTOR3* vec1, D3DXVECTOR3* vec2)
	{
		return GetDegree(acosf(D3DXVec3Dot(vec1, vec2)));
	}
	static float* FloatLerp(float* pOut, const float* pv1, const float* pv2, float s)
	{
		*pOut = (*pv1) + s * (*pv2 - *pv1);
		return pOut;
	}

	inline static VALIABLE m_MonochromeRate = { 0.0f,1.0f,1.0f,1.0f };
};

