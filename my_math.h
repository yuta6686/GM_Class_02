#pragma once
//  ---------------------------------------------------------
//  MyMath [my_math.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/05
//  ------------------------summary--------------------------
//  便利な関数をまとめてる
// 
// - ラジアンから度へ
// 
// - 度からラジアンへ
// 
// - 2つのベクトルの角度取得
// 
// - 線形補間関数（float,D3DXVECTOR3)
// 
// - ImVec4とD3DXCOLORの変換
// 
// - int型のランダム値範囲指定
// 
// - float型のランダム値範囲指定
// 
// - D3DXVECTOR3型のおランダム値範囲指定
// 
// - XとZ軸だけ、ランダムの値を返すD3DXVECTOR3の関数
// 
//  ---------------------------------------------------------

// https://protective-icon-1bc.notion.site/5fe08c879c9f41348026691e5d2e563b?v=6c4928c57afe4b5bbf80bc096fb0fccb

#include "renderer.h"
class MyMath
{
public:
//	静的変数
	inline static VALIABLE m_MonochromeRate = { 0.0f,1.0f,1.0f,1.0f };

//	静的関数
// 
	//	度からラジアンへ
	static float GetRadian(float degree) { return degree * (D3DX_PI / 180.0f); }
	static D3DXVECTOR3 GetRadian(D3DXVECTOR3 degree) { return degree * (D3DX_PI / 180.0f); }

	//	ラジアンから度へ
	static float GetDegree(float radian) { return radian * (180.0f / D3DX_PI); }
	static D3DXVECTOR3 GetDegree(D3DXVECTOR3 radian) { return radian * (180.0f / D3DX_PI); }

	//	2つのベクトルの角度取得
	static float GetViewAngle(D3DXVECTOR3* vec1, D3DXVECTOR3* vec2)
	{
		return GetDegree(acosf(D3DXVec3Dot(vec1, vec2)));
	}

	//	線形補間
	static float* FloatLerp(float* pOut, const float* pv1, const float* pv2, float s)
	{
		*pOut = (*pv1) + s * (*pv2 - *pv1);
		return pOut;
	}

	

	//	線形補間
	static void FromD3DXCOLORToImVec4(ImVec4* imc,const D3DXCOLOR& d3c)
	{
		imc->x = d3c.r;
		imc->y = d3c.g;
		imc->z = d3c.b;
		imc->w = d3c.a;
	}

	//	ImVec4 と D3DXCOLOR変換
	static void FromImVec4ToD3DXCOLOR(D3DXCOLOR* d3c, const ImVec4& imc)
	{
		d3c->r = imc.x;
		d3c->g = imc.y;
		d3c->b = imc.z;
		d3c->a = imc.w;
	}

	//	Random()関数(int)
	//	num1 ～ num2までの値を返す。
	static int Random(int min, int max) {
		int rnum, diff;
		if (min > max) {
			std::swap(min, max);
		}
		diff = max - min;
		rnum = min + rand() % diff;
		return rnum;
	}

	//	Random関数(float)
	static float Random(float min, float max)
	{
		float diff = max - min;
		float rnum = min + ((float)rand() / (float)RAND_MAX * diff);
		return rnum;
	}

	//	Random_Vector3関数(D3DXVECTOR3)
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

