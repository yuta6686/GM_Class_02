#pragma once
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "texture.h"
#include "ResourceManager.h"

// パーティクル用頂点レイアウト
struct VERTEX_3D_PARTICLE
{
	D3DXVECTOR3 Position;
	D3DXVECTOR2 TexCoord;
};
//今回使うパーティクルの資料例
struct ParticleCompute {
	// 座標
	D3DXVECTOR3 pos;
	// 速度
	D3DXVECTOR3 vel;
	// ライフ
	float life;
};

class ComputeShaderTest :public GameObject
{
private:
	int mParticleAmount = 100;

	inline static const int PARTICLE_MAX = 1000;
	inline static const std::vector<std::string> m_TextureName
		= {
		"asset\\texture\\particle_rect.png",
		"asset\\texture\\particle_rect_outline.png",
		"asset\\texture\\particle_triangle.png",
		"asset\\texture\\particle_triangle_outline.png",
		"asset\\texture\\particle_circle.png",
		"asset\\texture\\particle_circle_outline.png",
	};

	std::vector<std::shared_ptr<Resource>>  m_Textures;

	std::shared_ptr <VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;
public:


	// GameObject を介して継承されました
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

private:

	// コンピュートシェーダー
	ID3D11ComputeShader* mComputeShader;
	// パーティクル
	ParticleCompute* mparticle;
	// バッファ
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mpParticleBuffer;
	ID3D11Buffer* mpResultBuffer;
	ID3D11Buffer* mpPositionBuffer;
	// SRV
	ID3D11ShaderResourceView* mpParticleSRV;
	ID3D11ShaderResourceView* mpPositionSRV;
	// UAV
	ID3D11UnorderedAccessView* mpResultUAV;
};