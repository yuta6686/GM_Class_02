#include "stage_corridor.h"


void stage_corridor::Init()
{
	m_Model = ResourceManager<Model>::GetResource("asset\\model\\M_kairou.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(3.14f * 3.0f/2.0f , 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.324f, 0.565f, 0.324f);



	m_VertexShader = ResourceManager<VertexShader>::GetResource("vertexLightingVS.cso");
	m_PixelShader = ResourceManager<PixelShader>::GetResource("vertexLightingPS.cso");

}
void stage_corridor::Uninit()
{
}

void stage_corridor::Update()
{
}

void stage_corridor::Draw()
{
	//VertexShaderのDraw読んでからPixelShaderのDraw
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
