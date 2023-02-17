#include "stage_otorii.h"


void stage_otorii::Init()
{
	m_Model = ResourceManager<Model>::GetResource("asset\\model\\M_otorii.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float scale = 1.1f;
	m_Scale = D3DXVECTOR3(scale, scale, scale);

	m_VertexShader = 
		ResourceManager<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_DEFAULT]);
	m_PixelShader = 
		ResourceManager<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_DEFAULT]);
}

void stage_otorii::Uninit()
{
}

void stage_otorii::Update()
{
}

void stage_otorii::Draw()
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
