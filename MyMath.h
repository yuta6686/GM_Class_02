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

	static void FromD3DXCOLORToImVec4(ImVec4* imc,const D3DXCOLOR& d3c)
	{
		imc->x = d3c.r;
		imc->y = d3c.g;
		imc->z = d3c.b;
		imc->w = d3c.a;
	}

	static void FromImVec4ToD3DXCOLOR(D3DXCOLOR* d3c, const ImVec4& imc)
	{
		d3c->r = imc.x;
		d3c->g = imc.y;
		d3c->b = imc.z;
		d3c->a = imc.w;
	}

	//	Random()ŠÖ”
	//	num1 ` num2‚Ü‚Å‚Ì’l‚ð•Ô‚·B
	static int Random(int min, int max) {
		int rnum, diff;
		if (min > max) {
			std::swap(min, max);
		}
		diff = max - min;
		rnum = min + rand() % diff;
		return rnum;
	}

	static float Random(float min, float max)
	{
		float diff = max - min;
		float rnum = min + ((float)rand() / (float)RAND_MAX * diff);
		return rnum;
	}

	static D3DXVECTOR3 VEC3Random(float min, float max)
	{
		D3DXVECTOR3 random;
		random.x = Random(min, max);
		random.y = Random(min, max);
		random.z = Random(min, max);
		return random;
	}

	static D3DXVECTOR3 XZRandom(float min, float max)
	{
		D3DXVECTOR3 random;
		random.x = Random(min, max);
		random.y = 0.0f;
		random.z = Random(min, max);
		return random;
	}
};

