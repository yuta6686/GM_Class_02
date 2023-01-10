#include "stage_corridor_corner.h"


void stage_corridor_corner::Init()
{
	m_Model = ResourceManger<Model>::GetResource("asset\\model\\M_kairou_corner.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1, 1, 1);



	m_VertexShader = ResourceManger<VertexShader>::GetResource("vertexLightingVS.cso");
	m_PixelShader = ResourceManger<PixelShader>::GetResource("vertexLightingPS.cso");
}

void stage_corridor_corner::Uninit()
{
}

void stage_corridor_corner::Update()
{
}

void stage_corridor_corner::Draw()
{//VertexShaderのDraw読んでからPixelShaderのDraw
	m_VertexShader->Draw();
	m_PixelShader->Draw();


	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	m_Model->Draw();
}
