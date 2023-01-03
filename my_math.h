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

enum AXIS
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_XY,
	AXIS_XZ,
	AXIS_YZ,
	AXIS_XYZ
};

class MyMath
{
	inline static const float IKD_EPSIRON = 0.00001f;
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

	//https://yuta6686.atlassian.net/browse/AS-4
	///////////////////////////////////////////////////
	// 球と無限レイの衝突判定
	// r          : 球の半径
	// center     : 球の中心点
	// s          : レイの開始点
	// v          : レイの方向ベクトル
	// pOut_colli : 衝突位置
	// pOut_t     : 衝突時刻（出力）
	// 戻り値     : 衝突(true), 非衝突(false)
	static bool CalcSphereRayCollision(
		float r,
		D3DXVECTOR3* center,
		D3DXVECTOR3* s,
		D3DXVECTOR3* v,
		D3DXVECTOR3* pOut_colli,
		float* pOut_t
	) {
		D3DXVECTOR3 u = *s - *center;

		float a = D3DXVec3Dot(v, v);
		float b = D3DXVec3Dot(v, &u);
		float c = D3DXVec3Dot(&u, &u) - r * r;

		if (a - IKD_EPSIRON <= 0.0f) {
			// 誤差
			return false;
		}

		float isColli = b * b - a * c;
		if (isColli < 0.0f) {
			// 衝突しない
			return false;
		}

		float t = (-b - sqrt(b * b - a * c)) / a;

		if (pOut_t) {
			*pOut_t = t;
		}

		if (pOut_colli) {
			*pOut_colli = *s + *v * t;
		}

		// 衝突している
		return true;
	}

	///////////////////////////////////////////////////
	// スクリーン座標をワールド座標へ変換
	// out    : ワールド座標（出力）
	// pDev   : 描画デバイス
	// sx, xy : スクリーン座標
	// z      : スクリーン座標の仮想的なZ成分（0.0～1.0）
	// view   : ビュー行列
	// proj   : 射影変換行列
	// 戻り値 : ワールド座標（出力）
	static D3DXVECTOR3* transScreenToWorld(
		D3DXVECTOR3* out,		
		int sx,
		int sy,
		float z,
		D3DXMATRIX* view,
		D3DXMATRIX* proj
	) {
		// ビューポート行列を作成
		D3DXMATRIX vpMat;
		D3DXMatrixIdentity(&vpMat);
		
		D3D11_VIEWPORT vp;
		UINT num = 1;
		Renderer::GetDeviceContext()->RSGetViewports(&num, &vp);
		
		

		vpMat._11 = (float)vp.Width / 2;
		vpMat._22 = -1.0f * (float)(vp.Height / 2);
		vpMat._33 = (float)vp.MaxDepth - vp.MinDepth;
		vpMat._41 = (float)(vp.TopLeftX + vp.Width / 2);
		vpMat._42 = (float)(vp.TopLeftY + vp.Height / 2);
		vpMat._43 = vp.MinDepth;

		// スクリーン位置をワールドへ
		out->x = (float)sx;
		out->y = (float)sy;
		out->z = z;

		D3DXMATRIX invMat, inv_proj, inv_view;
		D3DXMatrixInverse(&invMat, 0, &vpMat);
		D3DXMatrixInverse(&inv_proj, 0, proj);
		D3DXMatrixInverse(&inv_view, 0, view);

		invMat *= inv_proj * inv_view;

		return D3DXVec3TransformCoord(out, out, &invMat);
	}
};

