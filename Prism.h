#pragma once
#include "component_object.h"

class Prism :
    public ComponentObject
{
private:
	// マクロ用変数
	inline const static float VALUE_MOVE = 5.0f;
	inline const static float VALUE_ROTATE = D3DX_PI * 0.02f;

	inline const static float SIZE_X = 640.0f;
	inline const static float SIZE_Y = 480.0f;

	// 通常変数
	inline static ID3D11Buffer* _vertexBufferPrism = nullptr;

	ID3D11ShaderResourceView* _baseTexture;
	ID3D11ShaderResourceView* _normalTexture;
	ID3D11ShaderResourceView* _envTexture;
	inline const static std::string _textureName = "asset\\texture\\swordOfKirito.png";

	std::shared_ptr <VertexShader> _vertexShader;
	std::shared_ptr<PixelShader> _pixelShader;
public:
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void DrawImgui()override;
private:
	
	D3DXMATRIX		matWorld;				// ワールド変換マトリックス
private:
	//----- プリズム面モデル定義
//　（注意）法線ベクトル、テクスチャ座標は計算で求める
	inline static VERTEX_3D prism_vertex[] = {
		//	Position						Normal				Diffuse						TexCoord
		{	{   0.0f,    0.0f, -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面０（右上）
		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２

		{	{   0.0f,    0.0f, -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面１（右下）
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２

		{	{   0.0f,    0.0f, -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面２（左下）
		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２

		{	{   0.0f,    0.0f,  -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面３（左上）
		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２
// --------------------------------------------------------------------------------------------------------------------------------
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２
		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面０（右上）

		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面１（右下）

		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２
		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面２（左下）

		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点２
		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点１
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// 頂点０　面３（左上）
	};

	inline static const int _prism_vertex_num = sizeof(prism_vertex) / sizeof(VERTEX_3D);

	typedef struct {
		int			status;		// ステータス
		D3DXVECTOR3	position;	// 座標
		D3DXVECTOR3	rotation;	// 回転角
		D3DXVECTOR3 size;
	} PRISM;

	PRISM g_Prism;
};

