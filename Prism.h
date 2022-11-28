#pragma once
#include "component_object.h"

class Prism :
    public ComponentObject
{
private:
	// �}�N���p�ϐ�
	inline const static float VALUE_MOVE = 5.0f;
	inline const static float VALUE_ROTATE = D3DX_PI * 0.02f;

	inline const static float SIZE_X = 640.0f;
	inline const static float SIZE_Y = 480.0f;

	// �ʏ�ϐ�
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
	
	D3DXMATRIX		matWorld;				// ���[���h�ϊ��}�g���b�N�X
private:
	//----- �v���Y���ʃ��f����`
//�@�i���Ӂj�@���x�N�g���A�e�N�X�`�����W�͌v�Z�ŋ��߂�
	inline static VERTEX_3D prism_vertex[] = {
		//	Position						Normal				Diffuse						TexCoord
		{	{   0.0f,    0.0f, -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂO�i�E��j
		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q

		{	{   0.0f,    0.0f, -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂP�i�E���j
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q

		{	{   0.0f,    0.0f, -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂQ�i�����j
		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q

		{	{   0.0f,    0.0f,  -250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂR�i����j
		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q
// --------------------------------------------------------------------------------------------------------------------------------
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q
		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂO�i�E��j

		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q
		{	{ 250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂP�i�E���j

		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q
		{	{   0.0f, -250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂQ�i�����j

		{	{   0.0f,  250.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q
		{	{-250.0f,    0.0f,    0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
		{	{   0.0f,    0.0f,  250.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂR�i����j
	};

	inline static const int _prism_vertex_num = sizeof(prism_vertex) / sizeof(VERTEX_3D);

	typedef struct {
		int			status;		// �X�e�[�^�X
		D3DXVECTOR3	position;	// ���W
		D3DXVECTOR3	rotation;	// ��]�p
		D3DXVECTOR3 size;
	} PRISM;

	PRISM g_Prism;
};

