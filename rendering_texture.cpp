#include "rendering_texture.h"
#include "user_interface_component.h"



void RenderingTexture::Init()
{
	// 頂点データ初期化
	m_vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[0].Diffuse = m_Color;
	m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x, 0.0f, 0.0f);
	m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[1].Diffuse = m_Color;
	m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	m_vertex[2].Position = D3DXVECTOR3(0.0f, m_mainPos.y, 0.0f);
	m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[2].Diffuse = m_Color;
	m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
	m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vertex[3].Diffuse = m_Color;
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

	m_Position = { 0.0f,0.0f,0.0f };
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };

	m_TypeName = "RenderingTexture";

	// RenderingTextureは複数あるので一つだけ持つようにする
	if(auto obj = Manager::GetScene()->GetGameObjects<RenderingTexture>().size() == 0)
	{
		AddComponent<ImGuiComponent>(COMLAYER_FIRST)->SetIsUse(true);	
	}


//---------------------------------
	ComponentObject::Init();
}

void RenderingTexture::Uninit()
{
	m_VertexBuffer->Release();
//---------------------------------
	ComponentObject::Uninit();
}

void RenderingTexture::Update()
{

//---------------------------------
	ComponentObject::Update();
}

void RenderingTexture::Draw()
{	


	ComponentObject::Draw();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	Renderer::SetWorldViewProjection2D();

	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale,
		GetScale().x,
		GetScale().y,
		GetScale().z);
	D3DXMatrixRotationYawPitchRoll(&rot,
		GetRotation().x,
		GetRotation().y,
		GetRotation().z);
	D3DXMatrixTranslation(&trans,
		GetPosition().x,
		GetPosition().y,
		GetPosition().z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;


	//テクスチャ設定
	switch (_layerNum)
	{	
	case LAYER_LUMINANCE:
		Renderer::SetRenderTexture(false);
		break;
	case LAYER_BLUR_X:
		viewport.Width = Renderer::BLUR_X_SCREEN;
		Renderer::SetLuminanceTexture();
		break;
	case LAYER_BLUR_Y:
		viewport.Width = Renderer::BLUR_X_SCREEN;
		viewport.Height = Renderer::BLUR_Y_SCREEN;
		Renderer::SetBlurXTexture();
		break;
	case LAYER_COPY:
		// ここでブラーの有無切り替えできる。
		if (MyImgui::_myFlag[_typeName])
		{
			// ブラー処理後のテクスチャ
			Renderer::SetBlurYTexture();		
		}
		else
		{
			// 無加工のテクスチャ
			Renderer::SetRenderTexture(false);		
		} 				
		break;
	case LAYER_RENDERING_TEXTURE:
		Renderer::SetCopyTexture();		
		break;
	case LAYER_BLOOM:
		// ブラー処理後のテクスチャ
		Renderer::SetBlurYTexture();
		
		// 加算合成に変更する
		//Renderer::SetAddBlend();

		break;
	default:
		break;
	}
	Renderer::GetDeviceContext()->RSSetViewports(1, &viewport);
	

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	Renderer::SetRenderTexture(true);

	// ブレンドモードを通常に直す
	Renderer::SetDefaultBlend();
}

void RenderingTexture::DrawImgui()
{	
	if (MyImgui::_myFlag["RenderingTexture"] && ImGui::CollapsingHeader("RenderingTexture")) {
		ImGui::Checkbox(_typeName.c_str(), &MyImgui::_myFlag[_typeName]);

		static float _strength = 8.0f;

		ImGui::SliderFloat("Blur Strength", &_strength, 0.1f, 100.0f);

		Renderer::SetBlur(_strength);
	}
}

