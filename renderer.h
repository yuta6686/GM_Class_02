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
private:

	static D3D_FEATURE_LEVEL		_featureLevel;

	static ID3D11Device*			_device;
	static ID3D11DeviceContext*		_deviceContext;
	static IDXGISwapChain*			_swapChain;

	//�f�B�X�v���C�̃o�b�O�o�b�t�@�̃e�N�X�`��	
	inline static ComPtr<ID3D11Texture2D> _pTexture;
	inline static ComPtr<ID3D11Texture2D> _pTextureX;
	inline static ComPtr<ID3D11Texture2D> _pTextureY;
	inline static ComPtr<ID3D11Texture2D> _pTextureDraw;

	// �T���v���[
	inline static ComPtr<ID3D11SamplerState> _pDefaultSampler;
	inline static ComPtr<ID3D11SamplerState> _pRenderTextureSampler;

	// ���Ƃ��ƍ݂�RTV��DPS
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	// �I�t�X�N�p RTV
	inline static ID3D11RenderTargetView* _pRenderingTextureRTV = nullptr;
	inline static ID3D11RenderTargetView* _blurXRTV = nullptr;
	inline static ID3D11RenderTargetView* _blurYRTV = nullptr;
	inline static ID3D11RenderTargetView* _drawCopyRTV = nullptr;

	// �I�t�X�N�p SRV
	inline static ID3D11ShaderResourceView* _pRenderingTextureSRV = nullptr;
	inline static ID3D11ShaderResourceView* _blurXSRV = nullptr;
	inline static ID3D11ShaderResourceView* _blurYSRV = nullptr;
	inline static ID3D11ShaderResourceView* _drawCopySRV = nullptr;


	static ID3D11BlendState* m_BlendState;
	static ID3D11BlendState* m_BlendStateATC;
	static ID3D11BlendState* m_BlendStateADDATC;

	static ID3D11RasterizerState* m_RS_Wireframe;
	static ID3D11RasterizerState* m_RS_CullBack;
	static ID3D11RasterizerState* m_RS_CullNone;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static std::vector<ID3D11Buffer*>			m_LightBuffer;
	static ID3D11Buffer*			m_PointLightBuffer;
	static ID3D11Buffer* m_MonochoromBuffer;
	static ID3D11Buffer* _weightsBuffer;


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;	

	inline static const int m_LightNum = 1;


	inline static float m_ImGuiFontSize = 20.0f;
public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	/// <summary BeginOfScr()>
	/// �I�t�X�N���[�������_�����O�p��Begin�֐�
	/// - ShaderResourceView�̐؂�ւ����s��
	/// </summary>
	static void BeginOfScr();
	static void BeginBlurX();
	static void BeginBlurY();
	static void BeginCopyDraw();
	static void EndDef();

	static void SetDefaultConstantBuffer();

	static void SetAlphaToCoverage(bool Enable);
	static void SetAddBlend(bool Enable);
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

	/// <summary>
	/// �T���v���[�ƃe�N�X�`���ݒ������B
	/// Draw���A�e�N�X�`���ɓǂݍ���SRV��ݒ肷��̂Ɠ����C���[�W
	/// </summary>	
	static void SetRenderTexture(bool isdefault);
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
