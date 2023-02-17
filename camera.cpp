#include "renderer.h"
#include "camera.h"
#include "scene.h"

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
	std::shared_ptr<Scene> scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	if (player == nullptr)return;

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
	D3DXMatrixPerspectiveFovLH(&_projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&_projectionMatrix);
}

bool Camera::CheckView(const D3DXVECTOR3& Position,const float& Scale)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * _projectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	for (unsigned int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&wpos[i], &vpos[i], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Position;

	// 左面判定
	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);
		if (D3DXVec3Dot(&n, &v) < -Scale)
			return false;
	}

	// 右面判定
	{
		v1 = wpos[3] - m_Position;
		v2 = wpos[1] - m_Position;

		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Scale)
			return false;
	}

	// 上面判定
	{
		v1 = wpos[1] - m_Position;
		v2 = wpos[0] - m_Position;

		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Scale)
			return false;
	}

	// 下面判定
	{
		v1 = wpos[2] - m_Position;
		v2 = wpos[3] - m_Position;

		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Scale)
			return false;
	}
	return true;
}
