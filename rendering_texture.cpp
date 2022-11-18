#include "rendering_texture.h"
#include "UserInterfaceComponent.h"


void RenderingTexture::Init()
{
	// ���_�f�[�^������
	m_vertex[0].Position = D3DXVECTOR3(-m_mainPos.x, -m_mainPos.y, 0.0f);
	m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[0].Diffuse = m_Color;
	m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x, -m_mainPos.y, 0.0f);
	m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[1].Diffuse = m_Color;
	m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	m_vertex[2].Position = D3DXVECTOR3(-m_mainPos.x, m_mainPos.y, 0.0f);
	m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[2].Diffuse = m_Color;
	m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
	m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[3].Diffuse = m_Color;
	m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_vertex;
	

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Position = _screenHalf;
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };

	AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitNoMaterialShader();
//---------------------------------
	ComponentObject::Init();
}

void RenderingTexture::Uninit()
{
	m_VertexBuffer->Release();
//---------------------------------
	ComponentObject::Uninit();
}

void RenderingTexture::Update()
{

//---------------------------------
	ComponentObject::Update();
}

void RenderingTexture::Draw()
{
	ComponentObject::Draw();

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	Renderer::SetWorldViewProjection2D();

	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale,
		GetScale().x,
		GetScale().y,
		GetScale().z);
	D3DXMatrixRotationYawPitchRoll(&rot,
		GetRotation().x,
		GetRotation().y,
		GetRotation().z);
	D3DXMatrixTranslation(&trans,
		GetPosition().x,
		GetPosition().y,
		GetPosition().z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	//�e�N�X�`���ݒ�
	Renderer::SetRenderTexture(false);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

	Renderer::SetRenderTexture(true);


}
