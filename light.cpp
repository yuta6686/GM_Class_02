#include "light.h"
#include "scene.h"
#include "manager.h"

void Light::Init()
{
	// ライト初期化
	
	m_Light.Enable = true;
	m_Light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&m_Light.Direction, &m_Light.Direction);
	m_Light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light.EyePos = D3DXVECTOR3(0, 0, 0);
	Renderer::SetLight(m_Light);
}

void Light::Uninit()
{
}

void Light::Update()
{
	//	エネミー取得
	Scene* scene = Manager::GetScene();	
	Camera* camera = scene->GetGameObject<Camera>();
	m_Light.EyePos = camera->GetPosition();
	Renderer::SetLight(m_Light);
}

void Light::Draw()
{
}
