//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Yanagisawa Yuta
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(200.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-400.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

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
	//	�r���[�}�g���N�X�ݒ�
	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up = D3DXVECTOR3( 0.0f,1.0f,0.0f );
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target,&up);

	Renderer::SetViewMatrix(&viewMatrix);

	//	�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
