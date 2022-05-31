
#include "main.h"
#include "renderer.h"
#include "Enemy.h"
#include "model.h"


char texName[] = { "asset\\model\\torus.obj" };
float scale = 0.5f;

void Enemy::Init()
{
	m_Model = new Model();
	m_Model->Load(texName);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotateion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(scale, scale, scale);
}

void Enemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Update()
{
	if (GetKeyboardPress(DIK_W)) {
		m_Position.z += 1.0f;
	}
	if (GetKeyboardPress(DIK_S)) {
		m_Position.z -= 1.0f;
	}
}

void Enemy::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	////�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotateion.y, m_Rotateion.x, m_Rotateion.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
