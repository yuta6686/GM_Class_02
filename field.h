#pragma once
class Field
{
private:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotateion;
	D3DXVECTOR3 m_Scale;

	float m_pos;

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

