#include "result_polygon.h"


void ResultPolygon::Init()
{
	m_mainPos.x = SCREEN_WIDTH / 2.0f;
	m_mainPos.y = SCREEN_HEIGHT / 2.0f;

	m_mainPos = m_Offset;

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-m_mainPos.x, -m_mainPos.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_mainPos.x, -m_mainPos.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-m_mainPos.x, m_mainPos.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

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
	m_VertexShader = ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
	m_PixelShader = ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());

	m_Position = { 0.0f,0.0f,0.0f };
	m_Position += m_Offset;
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };
}

void ResultPolygon::Uninit()
{
	m_VertexBuffer->Release();
}

void ResultPolygon::Update()
{
}

void ResultPolygon::Draw()
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
