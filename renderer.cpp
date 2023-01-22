
#include "renderer.h"
#include "scene.h"


D3D_FEATURE_LEVEL       Renderer::_featureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::_device = NULL;
ID3D11DeviceContext* Renderer::_deviceContext = NULL;
IDXGISwapChain* Renderer::_swapChain = NULL;
ID3D11DepthStencilView* Renderer::m_DepthStencilView = NULL;

D11Buffer Renderer::m_WorldBuffer = NULL;
D11Buffer Renderer::m_ViewBuffer = NULL;
D11Buffer Renderer::m_ProjectionBuffer = NULL;
D11Buffer Renderer::m_MaterialBuffer = NULL;
std::vector<D11Buffer>			Renderer::m_LightBuffer(m_LightNum);
D11Buffer Renderer::m_PointLightBuffer = NULL;
D11Buffer Renderer::m_MonochoromBuffer = NULL;
D11Buffer Renderer::_weightsBuffer = NULL;

ID3D11DepthStencilState* Renderer::m_DepthStateEnable = NULL;
ID3D11DepthStencilState* Renderer::m_DepthStateDisable = NULL;

ID3D11BlendState* Renderer::m_BlendState = NULL;
ID3D11BlendState* Renderer::m_BlendStateATC = NULL;
ID3D11BlendState* Renderer::m_BlendStateADDATC = NULL;

ID3D11RasterizerState* Renderer::m_RS_Wireframe = NULL;
ID3D11RasterizerState* Renderer::m_RS_CullBack = NULL;
ID3D11RasterizerState* Renderer::m_RS_CullNone = NULL;

// 輝度抽出用 https://yuta6686.atlassian.net/browse/AS-29
#define RGBA16FLOAT



void Renderer::Init()
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetWindow();
	swapChainDesc.SampleDesc.Count = 1; // MSAA設定
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	// If the project is in a debug build, enable the debug layer.
	//	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	creationFlags = 0;
#endif

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		creationFlags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapChain,
		&_device,
		&_featureLevel,
		&_deviceContext);


	// テクスチャ設定 オフスク用
	D3D11_TEXTURE2D_DESC rtDesc;
	memset(&rtDesc, 0, sizeof(rtDesc));
	rtDesc.Width = SCREEN_WIDTH;
	rtDesc.Height = SCREEN_HEIGHT;
	rtDesc.MipLevels = 1;
	rtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// rtDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
#ifdef RGBA16FLOAT
	rtDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
#endif // RGBA16FLOAT

	rtDesc.SampleDesc.Count = 1;
	rtDesc.Usage = D3D11_USAGE_DEFAULT;
	rtDesc.ArraySize = 1;
	rtDesc.BindFlags =
		D3D11_BIND_RENDER_TARGET |
		D3D11_BIND_SHADER_RESOURCE |
		D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	rtDesc.CPUAccessFlags = 0;

	_device->CreateTexture2D(&rtDesc, 0, &_pTexture);
	assert(_pTexture);
	_device->CreateTexture2D(&rtDesc, 0, &_pTextureDraw);



	// ダウンサンプリング用
	rtDesc.Width = static_cast<UINT>(SCREEN_WIDTH / 2.0f);
	_device->CreateTexture2D(&rtDesc, 0, &_pTextureX);

	rtDesc.Height = static_cast<UINT>(SCREEN_HEIGHT / 2.0f);
	_device->CreateTexture2D(&rtDesc, 0, &_pTextureY);

	//	SRV設定 オフスク用
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

#ifdef RGBA16FLOAT
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
#endif // RGBA16FLOAT

	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = rtDesc.MipLevels;

	// https://yuta6686.atlassian.net/browse/AS-39 ComPtr導入
	// SRV作成
	hr = _device->CreateShaderResourceView(_pTexture.Get(), &srvDesc, _pRenderingTextureSRV.GetAddressOf());
	if (hr) {
		assert(_pRenderingTextureSRV);
	}
	hr = _device->CreateShaderResourceView(_pTextureDraw.Get(), &srvDesc, _drawCopySRV.GetAddressOf());
	if (hr) {
		assert(_drawCopyRTV);
	}

	// ダウンサンプリング用
	hr = _device->CreateShaderResourceView(_pTextureX.Get(), &srvDesc, _blurXSRV.GetAddressOf());
	if (hr) {
		assert(_blurXSRV);
	}

	hr = _device->CreateShaderResourceView(_pTextureY.Get(), &srvDesc, _blurYSRV.GetAddressOf());
	if (hr) {
		assert(_blurYSRV);
	}
	

	// レンダーターゲットビュー作成 (デフォルト)
	ID3D11Texture2D* renderTarget = NULL;
	_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	_device->CreateRenderTargetView(renderTarget, NULL, m_RenderTargetView.GetAddressOf());
	renderTarget->Release();

	// RTV 作成 オフスク用
	_device->CreateRenderTargetView(_pTexture.Get(), NULL, _pRenderingTextureRTV.GetAddressOf());
	assert(_pRenderingTextureRTV);

	_device->CreateRenderTargetView(_pTextureDraw.Get(), NULL, _drawCopyRTV.GetAddressOf());

	
	// ダウンサンプリング用
	_device->CreateRenderTargetView(_pTextureX.Get(), NULL, _blurXRTV.GetAddressOf());
	_device->CreateRenderTargetView(_pTextureY.Get(), NULL, _blurYRTV.GetAddressOf());
	

	// デプスステンシルバッファ作成
	ID3D11Texture2D* depthStencile = NULL;
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	_device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D/*MS*/;// 最後のMSをとると元にもどる
	depthStencilViewDesc.Flags = 0;
	_device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();


	_deviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView);
	//m_DeviceContext->OMSetRenderTargets(2, rts, m_DepthStencilView);


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGui::StyleColorsClassic();

	//	ゲージの色Progresbar
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.0f, 1.0f, 220.0f / 250.0f, 1.0f));

	//	ホバー色
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.3f, 0.85f, 0.875f, 0.4f));

	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.0f, 1.0f, 0.9f, 0.7f));

	//  ウィンドウの角丸み->多分角度
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 15.0f);

	////  ウィンドウボーダーサイズ
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 10.0f);

	////	ウィンドウのタイトルのアラインメント
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));

	//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20.0f, 20.0f));

	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.0f, 3.0f));

	//ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.0f, 10.0f));

	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(_device, _deviceContext);

	//	Fonts
	io.Fonts->AddFontFromFileTTF("imgui/misc/fonts/Roboto-Medium.ttf", m_ImGuiFontSize);
	//io.Fonts->Fonts[0]
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\arial.ttf", m_ImGuiFontSize, NULL, io.Fonts->GetGlyphRangesJapanese());

	//IM_ASSERT(font != NULL);



	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	_deviceContext->RSSetViewports(1, &viewport);



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;



	//	CULL_BACK
	_device->CreateRasterizerState(&rasterizerDesc, &m_RS_CullBack);

	//	CULL_NONE
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	_device->CreateRasterizerState(&rasterizerDesc, &m_RS_CullNone);

	//	FILL_WIREFRAME & CULL_BACK
	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	_device->CreateRasterizerState(&rasterizerDesc, &m_RS_Wireframe);

	//	これを関数化する
	_deviceContext->RSSetState(m_RS_CullBack);




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//ID3D11BlendState* blendState = NULL;	->メンバ変数にする
	_device->CreateBlendState(&blendDesc, &m_BlendState);

	blendDesc.AlphaToCoverageEnable = TRUE;
	_device->CreateBlendState(&blendDesc, &m_BlendStateATC);

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	_device->CreateBlendState(&blendDesc, &m_BlendStateADDATC);

	_deviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);



	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	_device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	_device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//深度無効ステート

	_deviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);


	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};

	// フィルタリング
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.MaxAnisotropy = 4;	
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;// アドレッシングモード
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// ミップマップ設定
	samplerDesc.MipLODBias = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;


	_device->CreateSamplerState(&samplerDesc, _pDefaultSampler.GetAddressOf());
	_deviceContext->PSSetSamplers(0, 1, _pDefaultSampler.GetAddressOf());

	_device->CreateSamplerState(&samplerDesc, _pRenderTextureSampler.GetAddressOf());


	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	_device->CreateBuffer(&bufferDesc, NULL,	m_WorldBuffer.GetAddressOf());
	_deviceContext->VSSetConstantBuffers(0, 1,	m_WorldBuffer.GetAddressOf());

	_device->CreateBuffer(&bufferDesc, NULL,	m_ViewBuffer.GetAddressOf());
	_deviceContext->VSSetConstantBuffers(1, 1, m_ViewBuffer.GetAddressOf());

	_device->CreateBuffer(&bufferDesc, NULL,	m_ProjectionBuffer.GetAddressOf());
	_deviceContext->VSSetConstantBuffers(2, 1, m_ProjectionBuffer.GetAddressOf());


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	_device->CreateBuffer(&bufferDesc, NULL,	m_MaterialBuffer.GetAddressOf());
	_deviceContext->VSSetConstantBuffers(3, 1, m_MaterialBuffer.GetAddressOf());


	bufferDesc.ByteWidth = sizeof(LIGHT);

	for (int i = 0; i < m_LightNum; i++) {
		_device->CreateBuffer(&bufferDesc, NULL, m_LightBuffer[i].GetAddressOf());
		_deviceContext->VSSetConstantBuffers(4, 1, m_LightBuffer[i].GetAddressOf());
		_deviceContext->PSSetConstantBuffers(4, 1, m_LightBuffer[i].GetAddressOf());
	}

	bufferDesc.ByteWidth = sizeof(VALIABLE);

	_device->CreateBuffer(&bufferDesc, NULL, m_MonochoromBuffer.GetAddressOf());
	_deviceContext->VSSetConstantBuffers(5, 1, m_MonochoromBuffer.GetAddressOf());
	_deviceContext->PSSetConstantBuffers(5, 1, m_MonochoromBuffer.GetAddressOf());

	const int NUM_WEIGHTS = 8;
	float weights[NUM_WEIGHTS];

	CalcWeightsTableFromGaussian(weights,
		NUM_WEIGHTS, 8.0f);

	bufferDesc.ByteWidth = sizeof(weights);
	_device->CreateBuffer(&bufferDesc, NULL, _weightsBuffer.GetAddressOf());
	_deviceContext->PSSetConstantBuffers(6, 1, _weightsBuffer.GetAddressOf());
	_deviceContext->UpdateSubresource(_weightsBuffer.Get(), 0, NULL, &weights, 0, 0);

	VALIABLE a;
	a.MonochoromeRate = 0.0f;
	a.pad1 = 1.0f;
	a.pad3 = 1.0f;
	a.pad3 = 1.0f;
	_deviceContext->UpdateSubresource(m_MonochoromBuffer.Get(), 0, NULL, &a, 0, 0);




	//bufferDesc.ByteWidth = sizeof(POINT_LIGHT);

	//m_Device->CreateBuffer(&bufferDesc, NULL, &m_PointLightBuffer);
	//m_DeviceContext->VSSetConstantBuffers(5, 1, &m_PointLightBuffer);
	//m_DeviceContext->PSSetConstantBuffers(5, 1, &m_PointLightBuffer);



	// ライト初期化
	/*LIGHT light{};
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.EyePos = D3DXVECTOR3(0, 0, 0);
	SetLight(light);*/

	// ライト初期化
	/*POINT_LIGHT ptlight{};
	ptlight.Enable = true;
	ptlight.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&ptlight.Direction, &ptlight.Direction);
	ptlight.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	ptlight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ptlight.EyePos = D3DXVECTOR3(0, 0, 0);
	ptlight.ptColor = D3DXCOLOR(15.0f, 0.0f, 0.0f, 0.0f);
	ptlight.ptPosition = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	ptlight.ptRange = 100.0f;
	SetPointLight(ptlight);*/


	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);
	material.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);
	material.Emission = D3DXCOLOR(0, 0, 0, 0);
	SetMaterial(material);

}



void Renderer::Uninit()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// https://yuta6686.atlassian.net/browse/AS-39 ComPtr導入


	_deviceContext->ClearState();
			

	_swapChain->Release();
	_deviceContext->Release();
	_device->Release();

}



//	
void Renderer::Begin()
{	
	_deviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView);
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_deviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
	_deviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	_isRenderTexture = false;
}

void Renderer::End()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	_swapChain->Present(1, 0);
}

void Renderer::BeginOfScr()
{
	_deviceContext->OMSetRenderTargets(1, _pRenderingTextureRTV.GetAddressOf(), m_DepthStencilView);

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	_deviceContext->ClearRenderTargetView(_pRenderingTextureRTV.Get(), clearColor);
	_deviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	_isRenderTexture = true;
}

void Renderer::BeginBlurX()
{
	_deviceContext->OMSetRenderTargets(1, _blurXRTV.GetAddressOf(), m_DepthStencilView);
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	_deviceContext->ClearRenderTargetView(_blurXRTV.Get(), clearColor);
	_deviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::BeginBlurY()
{
	_deviceContext->OMSetRenderTargets(1, _blurYRTV.GetAddressOf(), m_DepthStencilView);
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	_deviceContext->ClearRenderTargetView(_blurYRTV.Get(), clearColor);
	_deviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::BeginCopyDraw()
{
	_deviceContext->OMSetRenderTargets(1, _drawCopyRTV.GetAddressOf(), m_DepthStencilView);
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	_deviceContext->ClearRenderTargetView(_drawCopyRTV.Get(), clearColor);
	_deviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}


void Renderer::EndDef()
{
	// m_SwapChain->Present(1, 0);	
}

void Renderer::SetDefaultConstantBuffer()
{
	_deviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);
	_deviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);
	_deviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);
	_deviceContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);
	for (int i = 0; i < m_LightNum; i++) {
		_deviceContext->VSSetConstantBuffers(4, 1, &m_LightBuffer[i]);
		_deviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer[i]);
	}
	_deviceContext->VSSetConstantBuffers(5, 1, &m_MonochoromBuffer);
	_deviceContext->PSSetConstantBuffers(5, 1, &m_MonochoromBuffer);
}



void Renderer::SetBlendState(BLEND_MODE bm)
{
	/*g_BlendStateParam = bm;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	switch (g_BlendStateParam)
	{
	case BLEND_MODE_NONE:
		m_DeviceContext->OMSetBlendState(g_BlendStateNone, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ALPHABLEND:
		m_DeviceContext->OMSetBlendState(g_BlendStateAlphaBlend, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ADD:
		m_DeviceContext->OMSetBlendState(g_BlendStateAdd, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_SUBTRACT:
		m_DeviceContext->OMSetBlendState(g_BlendStateSubtract, blendFactor, 0xffffffff);
		break;
	}*/
}
/// <summary>
/// サンプラーとテクスチャ設定をする。
/// Draw時、テクスチャに読み込んだSRVを設定するのと同じイメージ
/// </summary>	
void Renderer::SetRenderTexture(bool isdefault)
{
	if (isdefault) {
		_deviceContext->PSSetSamplers(0, 1, _pDefaultSampler.GetAddressOf());
	}
	else
	{
		_deviceContext->PSSetSamplers(0, 1, _pRenderTextureSampler.GetAddressOf());
		_deviceContext->VSSetShaderResources(0, 1, _pRenderingTextureSRV.GetAddressOf());
		_deviceContext->PSSetShaderResources(0, 1, _pRenderingTextureSRV.GetAddressOf());
	}
}

void Renderer::SetBlurXTexture()
{
	_deviceContext->VSSetShaderResources(0, 1, _blurXSRV.GetAddressOf());
	_deviceContext->PSSetShaderResources(0, 1, _blurXSRV.GetAddressOf());
}

void Renderer::SetBlurYTexture()
{
	_deviceContext->VSSetShaderResources(0, 1, _blurYSRV.GetAddressOf());
	_deviceContext->PSSetShaderResources(0, 1, _blurYSRV.GetAddressOf());
}

void Renderer::SetCopyTexture()
{
	_deviceContext->PSSetShaderResources(0, 1, _drawCopySRV.GetAddressOf());
}

void Renderer::SetAlphaToCoverage(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		_deviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	else
		_deviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);
}

void Renderer::SetAddBlend(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		_deviceContext->OMSetBlendState(m_BlendStateADDATC, blendFactor, 0xffffffff);
	else
		_deviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);
}

void Renderer::SetDepthEnable(bool Enable)
{
	if (Enable)
		_deviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	else
		_deviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);

}

void Renderer::SetCullNone(bool Enable)
{
	if (Enable)
		_deviceContext->RSSetState(m_RS_CullNone);
	else
		_deviceContext->RSSetState(m_RS_CullBack);
}

void Renderer::SetCullBack(bool Enable)
{
	if (Enable)
		_deviceContext->RSSetState(m_RS_CullBack);
	else
		_deviceContext->RSSetState(m_RS_CullNone);
}

void Renderer::SetWireframe(bool Enable)
{
	if (Enable)
		_deviceContext->RSSetState(m_RS_Wireframe);
	else
		_deviceContext->RSSetState(m_RS_CullBack);
}

void Renderer::SetWorldViewProjection2D()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	_deviceContext->UpdateSubresource(m_WorldBuffer.Get(), 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	_deviceContext->UpdateSubresource(m_ViewBuffer.Get(), 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&projection, &projection);
	_deviceContext->UpdateSubresource(m_ProjectionBuffer.Get(), 0, NULL, &projection, 0, 0);

}

void Renderer::SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	_deviceContext->UpdateSubresource(m_WorldBuffer.Get(), 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	_deviceContext->UpdateSubresource(m_ViewBuffer.Get(), 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	_deviceContext->UpdateSubresource(m_ProjectionBuffer.Get(), 0, NULL, &projection, 0, 0);
}

void Renderer::SetMaterial(MATERIAL Material)
{
	_deviceContext->UpdateSubresource(m_MaterialBuffer.Get(), 0, NULL, &Material, 0, 0);
}

void Renderer::SetLight(LIGHT Light, const int& index)
{
	_deviceContext->UpdateSubresource(m_LightBuffer[index].Get(), 0, NULL, &Light, 0, 0);
}

void Renderer::SetValiable(VALIABLE val)
{
	_deviceContext->UpdateSubresource(m_MonochoromBuffer.Get(), 0, NULL, &val, 0, 0);
}

void Renderer::SetBlur(const float& strength)
{
	const int NUM_WEIGHTS = 8;
	float weights[NUM_WEIGHTS];

	CalcWeightsTableFromGaussian(weights,
		NUM_WEIGHTS, strength);
	
	_deviceContext->UpdateSubresource(_weightsBuffer.Get(), 0, NULL, &weights, 0, 0);
}



//void Renderer::SetPointLight(POINT_LIGHT Light)
//{
//	m_DeviceContext->UpdateSubresource(m_PointLightBuffer, 0, NULL, &Light, 0, 0);
//}
//
//void Renderer::SetLightEyePos(D3DXVECTOR3 pos)
//{
//	// ライト初期化
//	LIGHT light{};
//	light.Enable = true;
//	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
//	D3DXVec4Normalize(&light.Direction, &light.Direction);
//	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
//	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	light.EyePos = pos;
//	SetLight(light);
//}


void Renderer::CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName)
{

	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);



	_device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,0,4 * 13,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "BINORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0,4 * 16,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	_device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}

void Renderer::CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName)
{
	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	_device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}


// <summary>
/// ガウシアン関数を利用して重みテーブルを計算する
/// </summary>
/// <param name="weightsTbl">重みテーブルの記録先</param>
/// <param name="sizeOfWeightsTbl">重みテーブルのサイズ</param>
/// <param name="sigma">分散具合。この数値が大きくなると分散具合が強くなる</param>
void Renderer::CalcWeightsTableFromGaussian(float* weightsTbl, int sizeOfWeightsTbl, float sigma)
{
	// 重みの合計を記録する変数を定義する
	float total = 0;

	// ここからガウス関数を用いて重みを計算している
	// ループ変数のxが基準テクセルからの距離
	for (int x = 0; x < sizeOfWeightsTbl; x++)
	{
		weightsTbl[x] = expf(-0.5f * (float)(x * x) / sigma);
		total += 2.0f * weightsTbl[x];
	}

	// 重みの合計で除算することで、重みの合計を1にしている
	for (int i = 0; i < sizeOfWeightsTbl; i++)
	{
		weightsTbl[i] /= total;
	}
}