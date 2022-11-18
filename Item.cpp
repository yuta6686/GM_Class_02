#include "main.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "bullet.h"
#include "manager.h"
#include "scene.h"
#include "Item.h"
#include "resource_manager.h"

#define PLAYER_SPEED 0.25f

static char texName[] = { "asset\\model\\torii.obj" };
static float scale = 0.5f;

void item::Init()
{	
	m_Model = ResourceManger<Model>::GetResource(texName);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(scale, scale, scale);
}

void item::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void item::Update()
{
}

void item::Draw()
{//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	////シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
