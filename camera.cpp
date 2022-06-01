#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "manager.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{

}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	D3DXVECTOR3 playerPosition = scene->GetGameObject<Player>()->GetPosition();
	
	m_Position = playerPosition;
	m_Position.y = playerPosition.y + 2.5f;
	m_Position.z = playerPosition.z - 5.0f;

	m_Target = playerPosition;

	Renderer::SetLightEyePos(m_Position);
}

void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXMATRIX viewMatix;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatix, &m_Position, &m_Target,
		&up);

	Renderer::SetViewMatrix(&viewMatix);


	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}