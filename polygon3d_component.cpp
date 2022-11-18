//  ---------------------------------------------------------
//  Polygon3DComponent [Polygon3DComponent.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - wasureta
//  ---------------------------------------------------------
#include "polygon3d_component.h"
#include "gameObject.h"
#include "VertexInitialize.h"


void Polygon3DComponent::Init()
{
	VERTEX_3D vertex[4];
	if (m_IsVertical) {
		VertexInitialize::InitVertex_Vertical(vertex);
	}
	else
	{
		VertexInitialize::InitVertex_Horizontal(vertex);
	}
	


	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;	
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;		

	if (m_IsChangeVertex)
	{
		bd.Usage = D3D11_USAGE_DYNAMIC;
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

	if (m_IsCullNone) {
		Renderer::SetCullNone(true);
	}
	

	m_Texture->Draw();	

	Renderer::SetCullNone(false);

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

void Polygon3DComponent::ChangeVertexDraw(const D3DXVECTOR4& color)
{
	if (m_IsChangeVertex) {
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


		if (m_IsVertical) {
			VertexInitialize::InitVertex_Vertical(vertex, color);
		}
		else
		{
			VertexInitialize::InitVertex_Horizontal(vertex,color);
		}


		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}
}
