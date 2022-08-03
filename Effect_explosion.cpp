//----------------------------------------
//  爆発エフェクト		2022/06/13
//	ビルボード表示		Author:柳澤優太
//----------------------------------------

#include "effect_explosion.h"
#include "renderer.h"
#include "field.h"
#include "texture.h"
#include "ResourceManager.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include "VertexInitialize.h"

void Effect_explosion::Init()
{
	VERTEX_3D vertex[4];
	VertexInitialize::InitVertex_Vertical(vertex);
	

	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;	->
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;	->
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//	テクスチャ読み込み
	m_Texture = ResourceManger<Texture>::GetResource("asset\\texture\\effect_explosion.png");

	//	シェーダ読み込み
	m_VertexShader = ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
	m_PixelShader = ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());

	//	トランスフォーム初期化
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Count = 0;

	
}

void Effect_explosion::Uninit()
{
	m_VertexBuffer->Release();
}

void Effect_explosion::Update()
{
	m_Count++;

	if (m_Count >= TEX_NUM) {
		SetDestroy();
		return;
	}
}

void Effect_explosion::Draw()
{
	float x = m_Count % TEX_WIDHT_NUM * (1.0f / (float)TEX_WIDHT_NUM);
	float y = m_Count / TEX_HEIGHT_NUM * (1.0f / (float)TEX_HEIGHT_NUM);

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float widht = (1.0f / (float)TEX_WIDHT_NUM);
	float height = (1.0f / (float)TEX_HEIGHT_NUM);

	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(x, y);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(x + widht, y);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(x, y+height);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f,0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(x+widht, y+height);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	m_VertexShader->Draw();
	m_PixelShader->Draw();

	//	カメラのビューマトリクス取得
	std::shared_ptr<Scene> scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	D3DXMATRIX view = camera->GetViewMatrix();

	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);	//	逆行列

	invView._41 = 
	invView._42 = 
	invView._43 = 0.0f;

	//マトリクス設定
	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);	

	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale *invView* trans;	
	Renderer::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//SetBlendState(BLEND_MODE_ADD);

	Renderer::SetAlphaToCoverage(TRUE);

	m_Texture->Draw();

	Renderer::SetAlphaToCoverage(FALSE);
}
