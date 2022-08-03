#include "Polygon3DComponent.h"
#include "gameObject.h"
#include "VertexInitialize.h"


void Polygon3DComponent::Init()
{
	VERTEX_3D vertex[4];
	VertexInitialize::InitVertex_Vertical(vertex);


	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;	
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;		

	if (m_IsChangeVertex)
	{
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void Polygon3DComponent::Uninit()
{
	m_VertexBuffer->Release();
}

void Polygon3DComponent::Update()
{
}

void Polygon3DComponent::Draw()
{
	//頂点バッファ設定

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//SetBlendState(BLEND_MODE_ADD);

	if (IsUseAlphaToCoverage) {
		Renderer::SetAlphaToCoverage(TRUE);
	}	

	m_Texture->Draw();	

	Renderer::SetAlphaToCoverage(FALSE);
}

void Polygon3DComponent::DrawImgui()
{
}

void Polygon3DComponent::ChangeVertexDraw()
{
	if (m_IsChangeVertex) {
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}
}
