#pragma once
//  ---------------------------------------------------------
//  MyMath [my_math.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/05
//  ------------------------summary--------------------------
//  �֗��Ȋ֐����܂Ƃ߂Ă�
// 
// - ���W�A������x��
// 
// - �x���烉�W�A����
// 
// - 2�̃x�N�g���̊p�x�擾
// 
// - ���`��Ԋ֐��ifloat,D3DXVECTOR3)
// 
// - ImVec4��D3DXCOLOR�̕ϊ�
// 
// - int�^�̃����_���l�͈͎w��
// 
// - float�^�̃����_���l�͈͎w��
// 
// - D3DXVECTOR3�^�̂������_���l�͈͎w��
// 
// - X��Z�������A�����_���̒l��Ԃ�D3DXVECTOR3�̊֐�
// 
//  ---------------------------------------------------------

// https://protective-icon-1bc.notion.site/5fe08c879c9f41348026691e5d2e563b?v=6c4928c57afe4b5bbf80bc096fb0fccb

#include "renderer.h"
class MyMath
{
public:
//	�ÓI�ϐ�
	inline static VALIABLE m_MonochromeRate = { 0.0f,1.0f,1.0f,1.0f };

//	�ÓI�֐�
// 
	//	�x���烉�W�A����
	static float GetRadian(float degree) { return degree * (D3DX_PI / 180.0f); }
	static D3DXVECTOR3 GetRadian(D3DXVECTOR3 degree) { return degree * (D3DX_PI / 180.0f); }

	//	���W�A������x��
	static float GetDegree(float radian) { return radian * (180.0f / D3DX_PI); }
	static D3DXVECTOR3 GetDegree(D3DXVECTOR3 radian) { return radian * (180.0f / D3DX_PI); }

	//	2�̃x�N�g���̊p�x�擾
	static float GetViewAngle(D3DXVECTOR3* vec1, D3DXVECTOR3* vec2)
	{
		return GetDegree(acosf(D3DXVec3Dot(vec1, vec2)));
	}

	//	���`���
	static float* FloatLerp(float* pOut, const float* pv1, const float* pv2, float s)
	{
		*pOut = (*pv1) + s * (*pv2 - *pv1);
		return pOut;
	}

	

	//	���`���
	static void FromD3DXCOLORToImVec4(ImVec4* imc,const D3DXCOLOR& d3c)
	{
		imc->x = d3c.r;
		imc->y = d3c.g;
		imc->z = d3c.b;
		imc->w = d3c.a;
	}

	//	ImVec4 �� D3DXCOLOR�ϊ�
	static void FromImVec4ToD3DXCOLOR(D3DXCOLOR* d3c, const ImVec4& imc)
	{
		d3c->r = imc.x;
		d3c->g = imc.y;
		d3c->b = imc.z;
		d3c->a = imc.w;
	}

	//	Random()�֐�(int)
	//	num1 �` num2�܂ł̒l��Ԃ��B
	static int Random(int min, int max) {
		int rnum, diff;
		if (min > max) {
			std::swap(min, max);
		}
		diff = max - min;
		rnum = min + rand() % diff;
		return rnum;
	}

	//	Random�֐�(float)
	static float Random(float min, float max)
	{
		float diff = max - min;
		float rnum = min + ((float)rand() / (float)RAND_MAX * diff);
		return rnum;
	}

	//	Random_Vector3�֐�(D3DXVECTOR3)
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

