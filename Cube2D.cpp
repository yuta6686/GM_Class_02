#include "cube2d.h"

#include "scene.h"

#include "collision.h"

#define FRICTION				(0.5f)					// 摩擦
#define FPS						(60)					// FPS

using namespace std;

void Cube2D::Init()
{
	m_mainPos.x = 40.0f;
	m_mainPos.y = 30.0f;

	m_Radius = 100.0f;


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
	m_Texture = ResourceManger<Texture>::GetResource("asset\\texture\\gameover_bg.dds");
	m_VertexShader = ResourceManger<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_UNLIT]);
	m_PixelShader = ResourceManger<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_UNLIT]);
	

	m_Position = { 0.0f,0.0f,0.0f };
	m_Position += m_Offset;
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };

	m_Index = s_Index;
	s_Index++;

	m_Scene = Manager::GetScene();
		

}

void Cube2D::Uninit()
{
	m_VertexBuffer->Release();
}

void Cube2D::Update()
{

	//	座標更新
	m_Position += m_Speed;

	m_Rotation.z += m_zContinuousRotation;

	//　端での跳ね返り
	if (m_Position.x + m_mainPos.x >= SCREEN_WIDTH ||
		m_Position.x - m_mainPos.x  <= 0.0f)
	{
		m_Speed.x *= -1.0f;
	}

	if (m_Position.y + m_mainPos.y >= SCREEN_HEIGHT ||
		m_Position.y - m_mainPos.y <= 0.0f)
	{
		m_Speed.y *= -1.0f;
	}
}

void Cube2D::Draw()
{	
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
