#include "prism.h"

#include "resource.h"
#include "vertexShader.h"
#include "pixelShader.h"

void Prism::Init()
{
	// プリズムのバッファ生成
	D3D11_BUFFER_DESC bd = {};
	D3D11_SUBRESOURCE_DATA sd = {};

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bd.ByteWidth = sizeof(VERTEX_3D) * _prism_vertex_num; 
	sd.pSysMem = prism_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &_vertexBufferPrism);
	
	// 深度設定
	Renderer::SetDepthEnable(true);

//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset\\texture\\yellow\\js_diffuse.dds",
		NULL,
		NULL,
		&_baseTexture,
		NULL);

	assert(_baseTexture);

	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset\\texture\\yellow\\js_normal.dds",
		NULL,
		NULL,
		&_normalTexture,
		NULL);

	assert(_normalTexture);

	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		_textureName.c_str(),
		NULL,
		NULL,
		&_envTexture,
		NULL);

	assert(_envTexture);
	
// シェーダロード
	_vertexShader =
		ResourceManger<VertexShader>::GetResource("env_mapping_vs.cso");

	_pixelShader =
		ResourceManger<PixelShader>::
		GetResource(PixelShader::GetFileNames()[SHADER_ENVIRONMENT_MAPPING]);
}

void Prism::Uninit()
{
	if (_vertexBufferPrism)
	{
		_vertexBufferPrism->Release();
		_vertexBufferPrism = nullptr;
	}

	if (_baseTexture)
	{
		_baseTexture->Release();
		_baseTexture = nullptr;
	}
}

void Prism::Update()
{
	D3DXMATRIX		matRotateX;				// Ｘ軸回転マトリックス
	D3DXMATRIX		matRotateY;				// Ｙ軸回転マトリックス
	D3DXMATRIX		matRotateZ;				// Ｚ軸回転マトリックス
	D3DXMATRIX		matTrans;				// 平行移動マトリックス
	D3DXMATRIX		matRotation;			// 回転マトリックス（合成後）
	D3DXVECTOR3		v_norm;					// 法線ベクトル
	D3DXVECTOR3		v_norm2;				// 法線ベクトル（回転後）
	D3DXVECTOR3		v_vtx;					// モデルの頂点への位置ベクトル
	D3DXVECTOR3		v_vtx2;					// モデルの頂点への位置ベクトル（回転後）
	D3DXVECTOR3		v_view2;				// 頂点から視点へのベクトル
	D3DXVECTOR3		v_ref;					// 屈折ベクトル
	D3DXVECTOR3		v_tmp;					// テンポラリ
	D3DXVECTOR3		bg_norm;				// ＢＧ面の法線ベクトル
	D3DXVECTOR3		v_pos;					// 屈折ベクトルとテクスチャ面との交点
	D3DXVECTOR3		v0, v1, v2;				// プリズム面の法線ベクトル計算用
	float		ref_rate_v, ref_rate_t;	// 屈折ベクトル計算用一時変数
	float		rrv_rrt, rrv2_rrt2;
	float		ans_InnerProduct;
	float		tmp0;
	float		n;
	int			i;

	const float size = 0.05f;
	g_Prism.size = { size,size,size };

	switch (g_Prism.status)
	{
	case 0:
		// モデル角度、位置の初期化
		g_Prism.rotation = { 0, 0, 0 };
		g_Prism.position = { 5, 0, 0 };
		

		// プリズム面の法線ベクトルを計算・設定
		for (i = 0; i < 8; i++)
		{
			v0 = prism_vertex[i * 3 + 1].Position - prism_vertex[i * 3].Position;
			v1 = prism_vertex[i * 3 + 2].Position - prism_vertex[i * 3].Position;
			D3DXVec3Cross(&v2, &v0, &v1);
			D3DXVec3Normalize(&v2, &v2);	// 正規化
			prism_vertex[i * 3].Normal =
				prism_vertex[i * 3 + 1].Normal =
				prism_vertex[i * 3 + 2].Normal = v2;
		}
		g_Prism.status = 1;
		// THRU
	case 1:
		// キーによる視点位置およびプリズムモデルの移動
		if (GetAsyncKeyState(VK_UP) & 0x8000) g_Prism.position[1] += 2.0f;	// カーソル（上）
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) g_Prism.position[1] -= 2.0f;	// カーソル（下）
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) g_Prism.position[0] -= 2.0f;	// カーソル（左）
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) g_Prism.position[0] += 2.0f;	// カーソル（右）
		// 自動的に回転
		// g_Prism.rotation.z += 0.01f;
		break;
	default:
		break;
	}
	
	// ワールドマトリックス設定 
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale,
		g_Prism.size.x,
		g_Prism.size.y,
		g_Prism.size.z);
	D3DXMatrixRotationYawPitchRoll(&rot,
		g_Prism.rotation.x,
		g_Prism.rotation.y,
		g_Prism.rotation.z);
	D3DXMatrixTranslation(&trans,
		g_Prism.position.x,
		g_Prism.position.y,
		g_Prism.position.z);
	matWorld = scale * rot * trans;
	
	for (i = 0; i < 3 * 8; i++)		// モデルは３頂点＊8面
	{
		// プリズムモデルの頂点にある法線ベクトルをワールド空間へ「回転」
		v_norm = prism_vertex[i].Normal;
		D3DXVec3TransformCoord(&v_norm2, &v_norm, &matRotation);
		D3DXVec3Normalize(&v_norm2, &v_norm2);	// 正規化

		// モデルの頂点をワールド空間へ変換し、視点への方向ベクトルを求める
		v_vtx = prism_vertex[i].Position;
		D3DXVec3TransformCoord(&v_vtx2, &v_vtx, &matWorld);
		D3DXVECTOR3 cameravec = Manager::GetScene()->GetGameObject<Camera>()->GetPosition();
		D3DXVec3Normalize(&cameravec, &cameravec);
		//cameravec.x = fabs(cameravec.x);
		//cameravec.y = fabs(cameravec.y);
		//cameravec.z = fabs(cameravec.z);

		v_view2 = cameravec - v_vtx2;
		D3DXVec3Normalize(&v_view2, &v_view2);	// 正規化

		//========================================================================
		//
		//    ここに以下のようなプログラムを追加する
		//
		//    ＊　屈折の計算式から屈折ベクトルを求める　＊
		//　　１：屈折率（２個）を変数に設定（ 1.0 と 1.2 を使用）
		//　　２：屈折の計算式中にある「内積」値を計算
		//　　　　（使用する値は先に求めてある v_norm2 と v_view2 を利用）
		//　　３：屈折率、計算値を使って屈折ベクトル v_ref を求める
		//
		//========================================================================
		// （解答例）*************************************************************
		// 屈折の計算式から屈折ベクトルを求める
		ref_rate_v = 1.0f;
		ref_rate_t = 1.2f;
		rrv_rrt = ref_rate_v / ref_rate_t;
		rrv2_rrt2 = (ref_rate_v * ref_rate_v) / (ref_rate_t * ref_rate_t);
		ans_InnerProduct = D3DXVec3Dot(&v_norm2, &v_view2);
		tmp0 = rrv_rrt * ans_InnerProduct - sqrtf(1.0f - rrv2_rrt2 * (1.0f - ans_InnerProduct * ans_InnerProduct));
		v_ref = tmp0 * v_norm2 - rrv_rrt * v_view2;
		//************************************************************************

		// 屈折ベクトルの線上とテクスチャ面との交点を求める
		//
		// (公式)
		// 位置ベクトルx0の点からベクトルmの方向に直線を延ばすとき
		// 平面の法線ベクトルがn、平面上の任意の点の位置ベクトルをxとすると
		// 直線と平面の交点の位置ベクトルは
		//		x0 + ((x-x0)・n / m・n)m	※「・」はベクトル同士の内積
		// で求められる
		// https://risalc.info/src/line-plane-intersection-point.html
		//
		// OpenGL(右手座標系)とDirectX(左手座標系)の違い(Zが逆)に注意
		D3DXVECTOR3 cameraForward = Manager::GetScene()->GetGameObject<Camera>()->GetForward();
		D3DXVec3Normalize(&cameraForward, &cameraForward);
		v_tmp = D3DXVECTOR3(0.0f, 0.0f, -80.0f) - v_vtx2;	// ここの定数は適当
		bg_norm = cameraForward * -1.0f;			// ＢＧのテクスチャ面の法線ベクトル
		n = D3DXVec3Dot(&v_tmp, &bg_norm) / D3DXVec3Dot(&v_ref, &bg_norm);
		v_pos = v_vtx2 + n * v_ref;

		// 交点座標を実際のテクスチャ座標に変換
		prism_vertex[i].TexCoord.x = 0.5f + v_pos.x * 0.001f;
		prism_vertex[i].TexCoord.y = 0.5f + v_pos.y * 0.001f;

		// テクスチャ座標もOpenGLと上下が逆
		prism_vertex[i].TexCoord.y = 1 - prism_vertex[i].TexCoord.y;
	}
}

void Prism::Draw()
{
	// シェーダ
	_vertexShader->Draw();
	_pixelShader->Draw();

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	// 頂点バッファ更新
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Renderer::GetDeviceContext()->Map(_vertexBufferPrism, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, prism_vertex, sizeof(VERTEX_3D) * _prism_vertex_num);
	Renderer::GetDeviceContext()->Unmap(_vertexBufferPrism, 0);

	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBufferPrism, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// テクスチャ設定
	if (Renderer::_isRenderTexture) {
		Renderer::SetRenderTexture(true);
		Renderer::GetDeviceContext()->VSSetShaderResources(0, 1, &_baseTexture);
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &_baseTexture);
		Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &_normalTexture);
		Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, &_envTexture);
	}
	else
	{
		Renderer::SetRenderTexture(false);
	}

	


	Renderer::SetWorldMatrix(&matWorld);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(_prism_vertex_num, 0);
}

void Prism::DrawImgui()
{
}
