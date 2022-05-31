//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM		(200.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-400.0f)		// カメラの初期位置(Z座標)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

void Camera::Init()
{
	m_Position =	D3DXVECTOR3( 0.0f,2.0f,-5.0f);
	m_Target =		D3DXVECTOR3( 0.0f,0.0f,0.0f );
}

void Camera::Uninit()
{
}

void Camera::Update()
{
}

void Camera::Draw()
{
	//	ビューマトリクス設定
	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up = D3DXVECTOR3( 0.0f,1.0f,0.0f );
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,&up);

	Renderer::SetViewMatrix(&viewMatrix);

	//	プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
