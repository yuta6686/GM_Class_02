#include "main.h"
#include "renderer.h"
#include "field.h"
#include "texture.h"
#include "ResourceManager.h"

void Field::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f,10.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
	//D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
	//	"asset\\texture\\field1.jpg",
	//	NULL,
	//	NULL,
	//	&m_Texture,
	//	NULL);

	//assert(m_Texture);
	m_Texture = ResourceManger<Texture>::GetResource("asset\\texture\\water.png");

	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");*/

	m_VertexShader = ResourceManger<VertexShader>::GetResource(VertexShader::DEFAULT_VERTEX_SHADER.c_str());
	m_PixelShader = ResourceManger<PixelShader>::GetResource(PixelShader::DEFAULT_PIXEL_SHADER.c_str());

	m_Position =	D3DXVECTOR3( 0.0f,0.0f,0.0f );
	m_Rotation =	D3DXVECTOR3( 0.0f,0.0f,0.0f );
	m_Scale =		D3DXVECTOR3( 1.0f,1.0f,1.0f );
}

void Field::Uninit()
{
	m_VertexBuffer->Release();	
}

void Field::Update()
{
}

void Field::Draw()
{
	//VertexShaderのDraw読んでからPixelShaderのDraw
	m_VertexShader->Draw();
	m_PixelShader->Draw();

	////入力レイアウト設定
	//Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	////シェーダ設定
	//Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	//Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
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

	Renderer::SetAlphaToCoverage(TRUE);

	m_Texture->Draw();

	Renderer::SetAlphaToCoverage(FALSE);
}
