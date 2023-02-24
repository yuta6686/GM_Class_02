#include "user_interface_component.h"
#include "gameObject.h"

void UserInterfaceComponent::Init()
{
	m_mainPosDouble = m_mainPos * 2.0f;
	InitVertex();

	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	if (m_IsChangeVertex) {
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	}

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = m_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// m_Parent->SetPosition(m_Offset);
}

void UserInterfaceComponent::Uninit()
{
	m_VertexBuffer->Release();
}

void UserInterfaceComponent::Update()
{

}

void UserInterfaceComponent::Draw()
{
	if (!_isValidity)return;

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	m_Texture->Draw();
}

void UserInterfaceComponent::DrawImgui()
{
#ifdef _DEBUG	
	ImVec4 color;
	color.x = m_Color.x;
	color.y = m_Color.y;
	color.z = m_Color.z;
	color.w = m_Color.w;

	ImGui::ColorEdit4("Aim Ling Color", (float*)&color);

	m_Color.x = color.x;
	m_Color.y = color.y;
	m_Color.z = color.z;
	m_Color.w = color.w;

#endif // DEBUG
}

void UserInterfaceComponent::InitVertex()
{
	switch (m_DeployIndex)
	{

	case DEPLOY_LEFTUP:
		
		m_vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[0].Diffuse = m_Color;
		m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		m_vertex[1].Position = D3DXVECTOR3(m_mainPosDouble.x, 0.0f, 0.0f);
		m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[1].Diffuse = m_Color;
		m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		m_vertex[2].Position = D3DXVECTOR3(0.0f, m_mainPosDouble.y, 0.0f);
		m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[2].Diffuse = m_Color;
		m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		m_vertex[3].Position = D3DXVECTOR3(m_mainPosDouble.x, m_mainPosDouble.y, 0.0f);
		m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[3].Diffuse = m_Color;
		m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case DEPLOY_RIGHTUP:
		break;
	case DEPLOY_LEFTDOWN:
		break;
	case DEPLOY_RIGHTDOWN:
		break;
	case DEPLOY_LEFT_MOVE_RIGHT:
		m_vertex[0].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition, 0.0f, 0.0f);
		m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[0].Diffuse = m_Color;
		m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition + m_RightXPosition, 0.0f, 0.0f);
		m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[1].Diffuse = m_Color;
		m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		m_vertex[2].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition, m_mainPosDouble.y, 0.0f);
		m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[2].Diffuse = m_Color;
		m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition + m_RightXPosition, m_mainPosDouble.y, 0.0f);
		m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[3].Diffuse = m_Color;
		m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case DEPLOY_SEPALATE_UP_DOWN:
		m_vertex[0].Position = D3DXVECTOR3(-m_mainPos.x + m_UpXPosition, -m_mainPos.y, 0.0f);
		m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[0].Diffuse = m_Color;
		m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		
		m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x + m_UpXPosition, -m_mainPos.y, 0.0f);
		m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[1].Diffuse = m_Color;
		m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		
		m_vertex[2].Position = D3DXVECTOR3(-m_mainPos.x + m_DownXPosition, m_mainPos.y, 0.0f);
		m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[2].Diffuse = m_Color;
		m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		
		m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x + m_DownXPosition, m_mainPos.y, 0.0f);
		m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[3].Diffuse = m_Color;
		m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;

	case DEPLOY_CENTER:
	case DEPLOY_MAX:
	default:
		m_vertex[0].Position = D3DXVECTOR3(-m_mainPos.x, -m_mainPos.y, 0.0f);
		m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[0].Diffuse = m_Color;
		m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x, -m_mainPos.y, 0.0f);
		m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[1].Diffuse = m_Color;
		m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		m_vertex[2].Position = D3DXVECTOR3(-m_mainPos.x, m_mainPos.y, 0.0f);
		m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[2].Diffuse = m_Color;
		m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
		m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[3].Diffuse = m_Color;
		m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;

	}

}

void UserInterfaceComponent::ChangeVertex(VERTEX_3D* vertex)
{
	switch (m_DeployIndex)
	{

	case DEPLOY_LEFTUP:		
		vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		
		vertex[1].Position = D3DXVECTOR3(m_mainPosDouble.x, 0.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		
		vertex[2].Position = D3DXVECTOR3(0.0f, m_mainPosDouble.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		
		vertex[3].Position = D3DXVECTOR3(m_mainPosDouble.x, m_mainPosDouble.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case DEPLOY_RIGHTUP:
		break;
	case DEPLOY_LEFTDOWN:
		break;
	case DEPLOY_RIGHTDOWN:
		break;
	case DEPLOY_LEFT_MOVE_RIGHT:
		vertex[0].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition, 0.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition+m_RightXPosition, 0.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		vertex[2].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition, m_mainPosDouble.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		vertex[3].Position = D3DXVECTOR3(m_mainPos.x + m_LeftXPosition+m_RightXPosition, m_mainPosDouble.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case DEPLOY_SEPALATE_UP_DOWN:
		vertex[0].Position = D3DXVECTOR3(-m_mainPos.x + m_UpXPosition , -m_mainPos.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_mainPos.x + m_UpXPosition, -m_mainPos.y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-m_mainPos.x + m_DownXPosition, m_mainPos.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		vertex[3].Position = D3DXVECTOR3(m_mainPos.x + m_DownXPosition, m_mainPos.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;
	case DEPLOY_CENTER:
	case DEPLOY_MAX:
	default:
		vertex[0].Position = D3DXVECTOR3(-m_mainPos.x, -m_mainPos.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = m_Color;
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(m_mainPos.x, -m_mainPos.y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = m_Color;
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-m_mainPos.x, m_mainPos.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = m_Color;
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = m_Color;
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		break;

	}
}

void UserInterfaceComponent::ChangeVertexDraw()
{
	if (m_IsChangeVertex) {
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;		

		ChangeVertex(vertex);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}
}

