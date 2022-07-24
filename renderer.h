#pragma once
#include <vector>


#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"



struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};



struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];
};

struct LIGHT
{
	// ディレクションライト用のメンバ
	D3DXVECTOR3 dirDirection;   // ライトの方向
	float pad0;
	D3DXVECTOR3 dirColor;       // ライトのカラー
	float pad1;

	// ライト構造体にポイントライト用のメンバ変数を追加
	D3DXVECTOR3 ptPosition;     // 位置
	float pad2;             // パディング
	D3DXVECTOR3 ptColor;        // カラー
	float ptRange;          // 影響範囲

	// step-1 ライト構造体にスポットライト用のメンバ変数を追加
	D3DXVECTOR3 spPosition;
	float pad3;

	D3DXVECTOR3 spColor;
	float spRange;

	D3DXVECTOR3 spDirection;
	float spAngle;

	D3DXVECTOR3 eyePos;         // 視点の位置
	float pad4;

	D3DXVECTOR3 ambientLight;   // アンビエントライト
	float pad5;
};

enum BLEND_MODE
{
	BLEND_MODE_NONE,		//ブレンド無し
	BLEND_MODE_ALPHABLEND,	//αブレンド
	BLEND_MODE_ADD,			//加算ブレンド
	BLEND_MODE_SUBTRACT,	//減算ブレンド

	BLEDD_MODE_NUM
};


class Renderer
{
private:

	static D3D_FEATURE_LEVEL		m_FeatureLevel;

	static ID3D11Device*			m_Device;
	static ID3D11DeviceContext*		m_DeviceContext;
	static IDXGISwapChain*			m_SwapChain;

	//ディスプレイのバッグバッファのテクスチャ	
	static ComPtr<ID3D11Texture2D> m_pRTTex;

	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;
	static ID3D11BlendState* m_BlendState;
	static ID3D11BlendState* m_BlendStateATC;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static std::vector<ID3D11Buffer*>			m_LightBuffer;
	static ID3D11Buffer*			m_PointLightBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	inline static const int m_LightNum = 1;

#ifdef _DEBUG
	// Our state
	inline static bool show_demo_window = false;
	inline static bool show_another_window = false;
	inline static bool show_hello_world = true;
	inline static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	inline static ImVec4 window_color;
	
#endif // _DEBUG
	inline static float m_ImGuiFontSize = 28.0f;
public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetAlphaToCoverage(bool Enable);
	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light,const int& index);
	//static void SetPointLight(POINT_LIGHT Light);
	void SetBlendState(BLEND_MODE bm);
	

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }



	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static const int GetLightNum() { return m_LightNum; }

#ifdef _DEBUG
	static void imguiDraw();
#endif // _DEBUG
};
