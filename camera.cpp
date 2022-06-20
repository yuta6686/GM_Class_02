#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "manager.h"
#include "player.h"

#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)				// カメラの回転量

void Camera::Init()
{
	//D3DXMatrixIdentity(&m_ViewMatrix);

	m_Position = D3DXVECTOR3(0.0f, 2.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = m_Position.x - m_Target.x;
	vz = m_Position.z - m_Target.z;
	m_Length = sqrtf(vx * vx + vz * vz);
}

void Camera::Uninit()
{

}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	D3DXVECTOR3 playerPosition = player->GetPosition();	
	D3DXVECTOR3 playerForward = player->GetCameraForward();
	
	//	サードパーソンビュー
	m_Target = playerPosition + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_Position = playerPosition;
	m_Position += (m_Length * playerForward * -1) + D3DXVECTOR3(0.0f,2.0f,0.0f);

	//	ファーストパーソンビュー
	/*m_Target = playerForward + playerPosition;;
	m_Position = playerPosition;*/
	

	//Renderer::SetLightEyePos(m_Position);
}

void Camera::Draw()
{
	//ビューマトリクス設定
	
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target,
		&up);

	Renderer::SetViewMatrix(&m_ViewMatrix);


	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}