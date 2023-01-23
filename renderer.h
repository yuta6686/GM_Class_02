#pragma once

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
	// �f�B���N�V�������C�g�p�̃����o
	D3DXVECTOR3 dirDirection;   // ���C�g�̕���
	float pad0;
	D3DXVECTOR3 dirColor;       // ���C�g�̃J���[
	float pad1;

	// ���C�g�\���̂Ƀ|�C���g���C�g�p�̃����o�ϐ���ǉ�
	D3DXVECTOR3 ptPosition;     // �ʒu
	float pad2;             // �p�f�B���O
	D3DXVECTOR3 ptColor;        // �J���[
	float ptRange;          // �e���͈�

	D3DXVECTOR3 eyePos;         // ���_�̈ʒu
	float pad4;

	D3DXVECTOR3 ambientLight;   // �A���r�G���g���C�g
	float pad5;
};

struct VALIABLE {
	float MonochoromeRate;
	float pad1;
	float pad2;
	float pad3;
};

enum BLEND_MODE
{
	BLEND_MODE_NONE,		//�u�����h����
	BLEND_MODE_ALPHABLEND,	//���u�����h
	BLEND_MODE_ADD,			//���Z�u�����h
	BLEND_MODE_SUBTRACT,	//���Z�u�����h

	BLEDD_MODE_NUM
};


class Renderer
{
public:
	inline static const float BLUR_X_SCREEN = SCREEN_WIDTH / 2.0f;
	inline static const float BLUR_Y_SCREEN = SCREEN_HEIGHT / 2.0f;
private:

	static D3D_FEATURE_LEVEL		_featureLevel;

	static ID3D11Device*			_device;
	static ID3D11DeviceContext*		_deviceContext;
	static IDXGISwapChain*			_swapChain;

	//�f�B�X�v���C�̃o�b�O�o�b�t�@�̃e�N�X�`��	
	inline static Texture2D _pTexture;
	inline static Texture2D _pTextureBloom;
	inline static Texture2D _pTextureX;
	inline static Texture2D _pTextureY;
	inline static Texture2D _pTextureDraw;

	// �T���v���[
	inline static ComPtr<ID3D11SamplerState> _pDefaultSampler;
	inline static ComPtr<ID3D11SamplerState> _pRenderTextureSampler;

	// ���Ƃ��ƍ݂�RTV��DPS
	inline static D11RenderTargetView m_RenderTargetView = nullptr;
	static ID3D11DepthStencilView* m_DepthStencilView;

	// https://yuta6686.atlassian.net/browse/AS-39 ComPtr����
	// �I�t�X�N�p RTV
	inline static D11RenderTargetView _pRenderingTextureRTV = nullptr;
	inline static D11RenderTargetView _luminanceRTV = nullptr; // https://yuta6686.atlassian.net/browse/AS-41
	inline static D11RenderTargetView _blurXRTV = nullptr;
	inline static D11RenderTargetView _blurYRTV = nullptr;
	inline static D11RenderTargetView _drawCopyRTV = nullptr;

	// �I�t�X�N�p SRV
	inline static ShaderResourceView _pRenderingTextureSRV = nullptr;
	inline static ShaderResourceView _luminanceSRV = nullptr;
	inline static ShaderResourceView _blurXSRV = nullptr;
	inline static ShaderResourceView _blurYSRV = nullptr;
	inline static ShaderResourceView _drawCopySRV = nullptr;


	static BlendState m_BlendState;
	static BlendState m_BlendStateATC;
	static BlendState m_BlendStateADDATC;

	static RasterizerState m_RS_Wireframe;
	static RasterizerState m_RS_CullBack;
	static RasterizerState m_RS_CullNone;

	static D11Buffer			m_WorldBuffer;
	static D11Buffer			m_ViewBuffer;
	static D11Buffer			m_ProjectionBuffer;
	static D11Buffer			m_MaterialBuffer;
	static std::vector<D11Buffer>			m_LightBuffer;
	static D11Buffer			m_PointLightBuffer;
	static D11Buffer m_MonochoromBuffer;
	static D11Buffer _weightsBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;	

	inline static const int m_LightNum = 1;


	inline static float m_ImGuiFontSize = 20.0f;
public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	/// summary BeginOfScr()
	/// �I�t�X�N���[�������_�����O�p��Begin�֐�
	/// - ShaderResourceView�̐؂�ւ����s��		
	static void BeginOfScr();
	static void BeginLuminance();
	static void BeginBlurX();
	static void BeginBlurY();
	static void BeginCopyDraw();
	static void EndDef();

	static void SetDefaultConstantBuffer();

	static void SetDefaultBlend();
	static void SetAlphaToCoverage();
	static void SetAddBlend();
	static void SetDepthEnable(bool Enable);
	static void SetCullNone(bool Enable);
	static void SetCullBack(bool Enable);
	static void SetWireframe(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light,const int& index);	
	static void SetValiable(VALIABLE val);
	static void SetBlur(const float& strength);
	//static void SetPointLight(POINT_LIGHT Light);
	void SetBlendState(BLEND_MODE bm);

	
	/// �T���v���[�ƃe�N�X�`���ݒ������B
	/// Draw���A�e�N�X�`���ɓǂݍ���SRV��ݒ肷��̂Ɠ����C���[�W	
	static void SetRenderTexture(bool isdefault);
	static void SetLuminanceTexture();
	static void SetBlurXTexture();
	static void SetBlurYTexture();
	static void SetCopyTexture();

	static ID3D11Device* GetDevice( void ){ return _device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return _deviceContext; }

	

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static const int GetLightNum() { return m_LightNum; }

	inline static VALIABLE m_Valiable = { 0.0f,0.0f,0.0f,0.0f };
	inline static bool _isRenderTexture = true;


	static void CalcWeightsTableFromGaussian(float* weightsTbl, int sizeOfWeightsTbl, float sigma);
};
