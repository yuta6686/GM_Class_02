#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "manager.h"

void Camera::Init()
{
	//D3DXMatrixIdentity(&m_ViewMatrix);

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
	
	static D3DXVECTOR3 offset{ 0,2.5f,-5.0f };

	if (GetKeyboardPress(DIK_UP)) {
		offset.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_DOWN)) {
		offset.y += 0.1f;
	}

	if (GetKeyboardPress(DIK_LEFT)) {
		offset.x += 0.1f;
	}

	if (GetKeyboardPress(DIK_RIGHT)) {
		offset.x -= 0.1f;
	}

	m_Position = playerPosition;
	m_Position += offset;

	playerPosition.y += 2.0f;
	m_Target = playerPosition;
	

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