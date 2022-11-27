#include "stage_wator_field.h"


void stage_wator_field::Init()
{
	m_Model = ResourceManger<Model>::GetResource("asset\\model\\M_Wator_field.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float scale = 100.1f;
	m_Scale = D3DXVECTOR3(scale, scale, scale);

	m_VertexShader = ResourceManger<VertexShader>::GetResource("vertexLightingVS.cso");
	m_PixelShader = ResourceManger<PixelShader>::GetResource("vertexLightingPS.cso");
}

void stage_wator_field::Uninit()
{
}

void stage_wator_field::Update()
{
}

void stage_wator_field::Draw()
{
	//VertexShader��Draw�ǂ�ł���PixelShader��Draw
	m_VertexShader->Draw();
	m_PixelShader->Draw();


	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	m_Model->Draw();
}
