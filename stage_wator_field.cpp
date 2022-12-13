#include "stage_wator_field.h"
#include "texture_compoennt.h"

void stage_wator_field::Init()
{
	m_Model = ResourceManger<Model>::GetResource("asset\\model\\M_Wator_field.obj");

	m_Position = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float scale = 50.1f;
	m_Scale = D3DXVECTOR3(scale, scale, scale);

	m_VertexShader = ResourceManger<VertexShader>::GetResource("env_mapping_vs.cso");
	m_PixelShader = ResourceManger<PixelShader>::GetResource("env_mapping_ps.cso");

	//m_VertexShader = ResourceManger<VertexShader>::GetResource("MeshFieldVS.cso");
	//m_PixelShader = ResourceManger<PixelShader>::GetResource("MeshFieldPS.cso");

	AddComponent<TextureComponent>(COMLAYER_SHADER)->
		SetTextureAndSlot("asset\\texture\\normalmap.png", 1, true);

	AddComponent<TextureComponent>(COMLAYER_SHADER)->
		SetTextureAndSlot("asset\\texture\\envmap_2.dds", 2, true);

	ComponentObject::Init();
}

void stage_wator_field::Uninit()
{
	ComponentObject::Uninit();
}

void stage_wator_field::Update()
{
	ComponentObject::Update();
}

void stage_wator_field::Draw()
{

	ComponentObject::Draw();

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
