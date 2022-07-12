#include "Transition.h"

void Transition::FadeIn()
{
	if (m_IsFadeIn == false)return;

	if (m_Count >0) {
		m_Count--;
	}
	else {
		m_IsFadeIn = false;
		m_IsFinishFadeIn = true;
	}
}

void Transition::FadeOut()
{
	if (m_IsFadeOut == false)return;
	if (m_IsFadeIn == true)return;

	if (m_Count < FADE_TIME) {
		m_Count++;
	}
	else {
		m_IsFadeOut = false;
		m_IsTransition = true;
	}
}

void Transition::Init()
{
	UserInterface::Init();

	m_mainPos.x = SCREEN_WIDTH / 2.0f;
	m_mainPos.y = SCREEN_HEIGHT / 2.0f;

	m_vertex[0].Position = D3DXVECTOR3(-m_mainPos.x, -m_mainPos.y, 0.0f);
	m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x, -m_mainPos.y, 0.0f);
	m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	m_vertex[2].Position = D3DXVECTOR3(-m_mainPos.x, m_mainPos.y, 0.0f);
	m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
	m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
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

	m_Position = { 0.0f,0.0f,0.0f };
	m_Position += m_Offset;
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };

	m_IsFadeIn = false;
	m_IsFadeOut = false;

	m_IsFinishFadeIn = false;
	m_IsTransition = false;
}

void Transition::Uninit()
{
	UserInterface::Uninit();
}

void Transition::Update()
{
	UserInterface::Update();

	FadeIn();

	FadeOut();
	
}

void Transition::Draw()
{

	float y;
	y = (m_Count / 60.0f - 1.0f) * SCREEN_HEIGHT;

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;	


	vertex[0].Position = D3DXVECTOR3(0.0f, -m_mainPos.y + y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);


	vertex[1].Position = D3DXVECTOR3(m_mainPos.x * 2.0f, -m_mainPos.y+y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	vertex[2].Position = D3DXVECTOR3(0.0f, m_mainPos.y+y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0,1);

	vertex[3].Position = D3DXVECTOR3(m_mainPos.x * 2.0f, m_mainPos.y+y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1,1);

	UserInterface::Draw();
}
