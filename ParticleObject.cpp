#include "ParticleObject.h"
#include "ResourceManager.h"
#include "VertexInitialize.h"

void ParticleObject::Init()
{
	VERTEX_3D vertex[4];
	VertexInitialize::InitVertex_Vertical(vertex);
	//	VertexInitialize::InitVertex_Horizontal(vertex);

	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_VertexShader =
		ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
	m_PixelShader =
		ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());


	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_Camera = scene->GetGameObject<Camera>();
}

void ParticleObject::Uninit()
{
	m_VertexBuffer->Release();
}

void ParticleObject::Update()
{
}

void ParticleObject::Draw()
{
	//	シェーダ
	m_VertexShader->Draw();
	m_PixelShader->Draw();

	//	カメラのビューマトリクス取得				
	D3DXMATRIX view = m_Camera->GetViewMatrix();

	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);	//	逆行列

	invView._41 =
		invView._42 =
		invView._43 = 0.0f;

	//マトリクス設定
	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale,
		GetScale().x,
		GetScale().y,
		GetScale().z);

	D3DXMatrixTranslation(&trans,
		GetPosition().x,
		GetPosition().y,
		GetPosition().z);

	world = scale * invView * trans;
	Renderer::SetWorldMatrix(&world);


}
