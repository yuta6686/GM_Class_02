#include "ui_score.h"

#include "scene.h"

#include "game_scene.h"
#include "camera.h"

void UI_Score::Init()
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
	m_vertex[2].Diffuse = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f);	//	左下
	m_vertex[1].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);	//	右上
	m_vertex[3].Diffuse = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 0.5f);	//	右下

	m_vertex[3].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	m_vertex[2].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	m_vertex[1].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	m_vertex[0].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	頂点バッファ生成
	//	頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	//bd.Usage = D3D11_USAGE_DEFAULT;	->
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;	->
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

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
	m_Texture = ResourceManger<Texture>::GetResource("asset\\texture\\number.png");
	m_VertexShader = ResourceManger<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_UNLIT]);
	m_PixelShader = ResourceManger<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_UNLIT]);

	m_Position = { 0.0f,0.0f,0.0f };
	m_Offset.x = m_mainPos.x;
	m_Offset.y = m_mainPos.y;
	m_Position += m_Offset;
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };
}

void UI_Score::Uninit()
{
	UserInterface::Uninit();
}

void UI_Score::Update()
{
	UserInterface::Update();

	if (GetKeyboardPress(DIK_C)) {
		m_Count++;
	}
}

void UI_Score::Draw()
{
	int count = static_cast<int>(m_Count);

	//	下の桁から入ってる
	std::vector<int> digit(DIGIT_NUM);
	float x_mergine = X_MARGINE;

	for (int i = 0; i < DIGIT_NUM; i++) {
		digit[i] = count % 10;
		count /= 10;



		float x = digit[i] % TEX_WIDHT_NUM * (1.0f / (float)TEX_WIDHT_NUM);
		float y = digit[i] / TEX_HEIGHT_NUM * (1.0f / (float)TEX_HEIGHT_NUM);

		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float widht = (1.0f / (float)TEX_WIDHT_NUM);
		float height = (1.0f / (float)TEX_HEIGHT_NUM);


		vertex[0].Position = D3DXVECTOR3(x_mergine*i, -m_mainPos.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);


		vertex[1].Position = D3DXVECTOR3(x_mergine * i + m_mainPos.x * 2.0f, -m_mainPos.y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + widht, y);

		vertex[2].Position = D3DXVECTOR3(x_mergine * i, m_mainPos.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + height);

		vertex[3].Position = D3DXVECTOR3(x_mergine * i + m_mainPos.x * 2.0f, m_mainPos.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(x + widht, y + height);

		for (int i = 0; i < 4; i++) {
			vertex[i].Position += m_cOffset;
		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

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


		Renderer::SetAlphaToCoverage(TRUE);

		m_Texture->Draw();

		Renderer::SetAlphaToCoverage(FALSE);
	}
}
