#include "pointLight.h"
#include "scene.h"
#include "manager.h"

void PointLight::Init()
{
	// ƒ‰ƒCƒg‰Šú‰»

	m_ptLight.Enable = true;
	m_ptLight.Direction = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&m_ptLight.Direction, &m_ptLight.Direction);
	m_ptLight.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	m_ptLight.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	m_ptLight.EyePos = D3DXVECTOR3(0, 0, 0);
	m_ptLight.ptPosition = m_Position;
	m_ptLight.ptColor = D3DXCOLOR(5.0f, 0.0f, 0.0f,0.0f);
	m_ptLight.ptRange = 1000.0f;


	Renderer::SetPointLight(m_ptLight);
}

void PointLight::Uninit()
{
}

void PointLight::Update()
{	
	
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	//Player* player = scene->GetGameObject<Player>();


	m_ptLight.EyePos = camera->GetPosition();

	//m_Position = player->GetPosition();
	
	if (GetKeyboardPress(DIK_I)) {
		m_Position.z += 1.5f;
	}
	if (GetKeyboardPress(DIK_K)) {
		m_Position.z -= 1.5f;
	}

	if (GetKeyboardPress(DIK_J)) {
		m_Position.x -= 1.5f;
	}
	if (GetKeyboardPress(DIK_L)) {
		m_Position.x += 1.5f;
	}

	m_ptLight.ptPosition = { m_Position.x,m_Position.y+50.0f,m_Position.z };

	Renderer::SetPointLight(m_ptLight);
}

void PointLight::Draw()
{
}
