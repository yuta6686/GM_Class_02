#include "UI_Charge.h"
#include "ResourceManager.h"
#include <cmath>

void UI_Charge::Init()
{
	m_mainPos.x = MAIN_POS_X;
	m_mainPos.y = MAIN_POS_Y;

	m_Radius = sqrtf(m_mainPos.x * m_mainPos.x + m_mainPos.y * m_mainPos.y);


	m_vertex[0].Position = D3DXVECTOR3(0.0f, -m_mainPos.y, 0.0f);
	m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x * 2.0f, -m_mainPos.y, 0.0f);
	m_vertex[2].Position = D3DXVECTOR3(0.0f, m_mainPos.y, 0.0f);
	m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x * 2.0f, m_mainPos.y, 0.0f);

	m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vertex[0].Diffuse = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);	//	左上
	m_vertex[2].Diffuse = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);	//	左下
	m_vertex[1].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);	//	右上
	m_vertex[3].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);	//	右下

	m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	/*D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset\\texture\\Slimecyclon.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);*/
	m_Texture = ResourceManger<Texture>::GetResource("asset\\texture\\blender1.png");
	m_VertexShader = ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
	m_PixelShader = ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());

	m_Position = { 0.0f,0.0f,0.0f };
	m_Offset.x = 0.0f;
	m_Offset.y = SCREEN_HEIGHT - m_mainPos.y;
	m_Position += m_Offset;
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };

	m_Counter = 1.0f;
}

void UI_Charge::Uninit()
{
	UserInterface::Uninit();
}

void UI_Charge::Update()
{
	UserInterface::Update();

	m_Position.y = m_mainPos.y;
	
	if (m_Counter >= COUNTER_MAX) {
		m_Counter = 1.0f;
	}
	m_Counter+= CHARGE_SPEED;
	m_Scale.x = logf(m_Counter);


}

void UI_Charge::Draw()
{
	UserInterface::Draw();
}
