
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include <io.h>
#include <vector>

D3D_FEATURE_LEVEL       Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::m_Device = NULL;
ID3D11DeviceContext* Renderer::m_DeviceContext = NULL;
IDXGISwapChain* Renderer::m_SwapChain = NULL;
ComPtr<ID3D11Texture2D> Renderer::m_pRTTex = nullptr;
ID3D11RenderTargetView* Renderer::m_RenderTargetView = NULL;	//こいつに背景色入れてる
ID3D11DepthStencilView* Renderer::m_DepthStencilView = NULL;

ID3D11Buffer* Renderer::m_WorldBuffer = NULL;
ID3D11Buffer* Renderer::m_ViewBuffer = NULL;
ID3D11Buffer* Renderer::m_ProjectionBuffer = NULL;
ID3D11Buffer* Renderer::m_MaterialBuffer = NULL;
std::vector<ID3D11Buffer*>			Renderer::m_LightBuffer(m_LightNum);
ID3D11Buffer* Renderer::m_PointLightBuffer = NULL;
ID3D11Buffer* Renderer::m_MonochoromBuffer = NULL;

ID3D11DepthStencilState* Renderer::m_DepthStateEnable = NULL;
ID3D11DepthStencilState* Renderer::m_DepthStateDisable = NULL;

ID3D11BlendState* Renderer::m_BlendState = NULL;
ID3D11BlendState* Renderer::m_BlendStateATC = NULL;
ID3D11BlendState* Renderer::m_BlendStateADDATC = NULL;

ID3D11RasterizerState* Renderer::m_RS_Wireframe = NULL;
ID3D11RasterizerState* Renderer::m_RS_CullBack = NULL;
ID3D11RasterizerState* Renderer::m_RS_CullNone = NULL;





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
	swapChainDesc.SampleDesc.Count = 1;
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
		&m_SwapChain,
		&m_Device,
		&m_FeatureLevel,
		&m_DeviceContext);




	// スワップチェインに用意されたバッファ（2Dテクスチャ）を取得
	hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_pRTTex));
	if (FAILED(hr)) {
		return;
	}

	

	// レンダーターゲットView作成
	hr = m_Device->CreateRenderTargetView(m_pRTTex.Get(), NULL, &m_RenderTargetView);
	if (FAILED(hr)) {
		return;
	}

	// レンダーターゲットビュー作成
	/*ID3D11Texture2D* renderTarget = NULL;
	m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&renderTarget );
	m_Device->CreateRenderTargetView( renderTarget, NULL, &m_RenderTargetView );
	renderTarget->Release();*/

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
	m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();


	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);



	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

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
	ImGui_ImplDX11_Init(m_Device, m_DeviceContext);

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
	m_DeviceContext->RSSetViewports(1, &viewport);



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;



	//	CULL_BACK
	m_Device->CreateRasterizerState(&rasterizerDesc, &m_RS_CullBack);

	//	CULL_NONE
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	m_Device->CreateRasterizerState(&rasterizerDesc, &m_RS_CullNone);

	//	FILL_WIREFRAME & CULL_BACK
	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	m_Device->CreateRasterizerState(&rasterizerDesc, &m_RS_Wireframe);

	//	これを関数化する
	m_DeviceContext->RSSetState(m_RS_CullBack);




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
	m_Device->CreateBlendState(&blendDesc, &m_BlendState);

	blendDesc.AlphaToCoverageEnable = TRUE;
	m_Device->CreateBlendState(&blendDesc, &m_BlendStateATC);

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	
	m_Device->CreateBlendState(&blendDesc, &m_BlendStateADDATC);

	m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);



	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//深度無効ステート

	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	ID3D11SamplerState* samplerState = NULL;
	m_Device->CreateSamplerState(&samplerDesc, &samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);



	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_MaterialBuffer);
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	for (int i = 0; i < m_LightNum; i++) {
		m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer[i]);
		m_DeviceContext->VSSetConstantBuffers(4, 1, &m_LightBuffer[i]);
		m_DeviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer[i]);
	}

	bufferDesc.ByteWidth = sizeof(VALIABLE);
	
	m_Device->CreateBuffer(&bufferDesc, NULL, &m_MonochoromBuffer);
	m_DeviceContext->VSSetConstantBuffers(5, 1, &m_MonochoromBuffer);
	m_DeviceContext->PSSetConstantBuffers(5, 1, &m_MonochoromBuffer);

	VALIABLE a;
	a.MonochoromeRate = 0.0f;
	a.pad1 = 1.0f;
	a.pad3 = 1.0f;
	a.pad3 = 1.0f;
	m_DeviceContext->UpdateSubresource(m_MonochoromBuffer, 0, NULL, &a, 0, 0);

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


	m_WorldBuffer->Release();
	m_ViewBuffer->Release();
	m_ProjectionBuffer->Release();

	for (auto light : m_LightBuffer) {
		light->Release();
	}

	m_MaterialBuffer->Release();
	m_MonochoromBuffer->Release();


	m_DeviceContext->ClearState();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_DeviceContext->Release();
	m_Device->Release();

}



//	
void Renderer::Begin()
{
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}



void Renderer::End()
{


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());



	m_SwapChain->Present(1, 0);
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

void Renderer::SetAlphaToCoverage(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	else
		m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);
}

void Renderer::SetAddBlend(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		m_DeviceContext->OMSetBlendState(m_BlendStateADDATC, blendFactor, 0xffffffff);
	else
		m_DeviceContext->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);
}

void Renderer::SetDepthEnable(bool Enable)
{
	if (Enable)
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	else
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);

}

void Renderer::SetCullNone(bool Enable)
{
	if(Enable)		
		m_DeviceContext->RSSetState(m_RS_CullNone);
	else
		m_DeviceContext->RSSetState(m_RS_CullBack);
}

void Renderer::SetCullBack(bool Enable)
{
	if (Enable)
		m_DeviceContext->RSSetState(m_RS_CullBack);
	else
		m_DeviceContext->RSSetState(m_RS_CullNone);
}

void Renderer::SetWireframe(bool Enable)
{
	if (Enable)
		m_DeviceContext->RSSetState(m_RS_Wireframe);
	else
		m_DeviceContext->RSSetState(m_RS_CullBack);
}

void Renderer::SetWorldViewProjection2D()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&projection, &projection);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);

}

void Renderer::SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

void Renderer::SetMaterial(MATERIAL Material)
{
	m_DeviceContext->UpdateSubresource(m_MaterialBuffer, 0, NULL, &Material, 0, 0);
}

void Renderer::SetLight(LIGHT Light, const int& index)
{
	m_DeviceContext->UpdateSubresource(m_LightBuffer[index], 0, NULL, &Light, 0, 0);
}

void Renderer::SetValiable(VALIABLE val)
{
	m_DeviceContext->UpdateSubresource(m_MonochoromBuffer, 0, NULL, &val, 0, 0);
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



	m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	m_Device->CreateInputLayout(layout,
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

	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}

#ifdef _DEBUG
void Renderer::imguiDraw()
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);



	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, window_color);

		ImGui::Begin("Hello, world!", &show_hello_world);                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);
		ImGui::Checkbox("Hello World Window", &show_hello_world);

		std::shared_ptr<Scene> scene = Manager::GetScene();
		ImGui::Checkbox("Parameters by scene", &scene->parameters_by_scene);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		ImGui::ColorEdit4("window color", (float*)&window_color);




		ImGui::SetNextWindowSize(ImVec2(window_color.x, window_color.y));


		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			//counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Framerate : %.1f FPS", ImGui::GetIO().Framerate);
		ImGui::SameLine();
		ImGui::ProgressBar(ImGui::GetIO().Framerate / 60.0f);

		ImGui::Text("MousePosDiffX: %d \nMousePosDiffY: %d", GetMouseX(), GetMouseY());

		ImGui::Text("Mouse_X: %.f", ImGui::GetIO().MousePos.x);
		ImGui::SameLine();
		ImGui::ProgressBar(ImGui::GetIO().MousePos.x / SCREEN_WIDTH);

		ImGui::Text("Mouse_Y: %.f", ImGui::GetIO().MousePos.y);
		ImGui::SameLine();
		ImGui::ProgressBar(ImGui::GetIO().MousePos.y / SCREEN_HEIGHT);

		ImGui::End();

		ImGui::PopStyleColor();
	}


}
#endif // _DEBUG