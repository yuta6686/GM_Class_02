//  ---------------------------------------------------------
//  Transition [Transition.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/05
//  ------------------------summary--------------------------
//  - フェード処理
//  ---------------------------------------------------------
#include "transition.h"

#include "audio.h"


void Transition::Init()
{
	m_mainPos.x = SCREEN_WIDTH / 2.0f;
	m_mainPos.y = SCREEN_HEIGHT / 2.0f;

	m_vertex[0].Position = D3DXVECTOR3(-m_mainPos.x, -m_mainPos.y, 0.0f);
	m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[0].Diffuse = m_Diffuse;
	m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x, -m_mainPos.y, 0.0f);
	m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[1].Diffuse = m_Diffuse;
	m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	m_vertex[2].Position = D3DXVECTOR3(-m_mainPos.x, m_mainPos.y, 0.0f);
	m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[2].Diffuse = m_Diffuse;
	m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
	m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[3].Diffuse = m_Diffuse;
	m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;	->
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;	->
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Count = 0;

	m_Offset = { 0.0f,SCREEN_HEIGHT / 2.0f,0.0f };

	m_Texture = ResourceManager<Texture>::GetResource("asset\\texture\\noen_white.png");
	m_VertexShader = ResourceManager<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_UNLIT_NO_MATERIAL]);
	m_PixelShader = ResourceManager<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_UNLIT]);

	m_SE = Manager::GetScene()->AddGameObject<Audio>(LAYER_AUDIO);
	
	m_SE->Load("asset\\audio\\SE_Transition.wav");	
	m_SE->SetAudioVolume(0.5f);

	m_Position = { 0.0f,0.0f,0.0f };
	m_Position += m_Offset;
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };
}


void Transition::Uninit()
{
	m_VertexBuffer->Release();
}

void Transition::Update()
{
	if (m_In) {
		if (m_Count > 0)
			m_Count--;
	}
	else
	{
		if (m_Count < FADE_TIME)
			m_Count++;
		else
			m_Finish = true;
	}


}

void Transition::Draw()
{

	//float x;
	//x = ((m_Count / 60.0f)) * SCREEN_WIDTH * RATIO;	

	float count0to1 = powf(m_Count / 60.0f,4.0f);
	float xleft = count0to1 * SCREEN_WIDTH * RATIO;
	float xright = count0to1 * SCREEN_WIDTH * (1.0f - RATIO);

	float col = (m_Count / 60.0f);
	m_Diffuse.y = (1.0f-col);
	m_Diffuse.z = (1.0f-col);
	m_Diffuse.w = fmaxf(col + 0.2f, 1.0f);

	
	float ratio = (1.0f - (m_Count / 60.0f)) * RATIO;

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	

	vertex[0].Position = D3DXVECTOR3(m_OffsetX[0] - xleft , -m_mainPos.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = m_Diffuse;
	vertex[0].TexCoord = D3DXVECTOR2(ratio, 0);


	vertex[1].Position = D3DXVECTOR3(m_OffsetX[1] + xright, -m_mainPos.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = m_Diffuse;
	vertex[1].TexCoord = D3DXVECTOR2(1-ratio, 0);

	vertex[2].Position = D3DXVECTOR3(m_OffsetX[2] - xright , m_mainPos.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = m_Diffuse;
	vertex[2].TexCoord = D3DXVECTOR2(ratio, 1);

	vertex[3].Position = D3DXVECTOR3(m_OffsetX[3] + xleft, m_mainPos.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = m_Diffuse;
	vertex[3].TexCoord = D3DXVECTOR2(1-ratio, 1);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	m_VertexShader->Draw();
	m_PixelShader->Draw();

	//マトリクス設定	
	Renderer::SetWorldViewProjection2D();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);



	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	m_Texture->Draw();
}

void Transition::Start(bool in)
{
	m_In = in;
	m_Finish = false;

	m_SE->Play(false);

	if (m_In)
		m_Count = 60;
	else
		m_Count = 0;
}
