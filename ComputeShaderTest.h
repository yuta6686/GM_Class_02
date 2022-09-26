#pragma once
#include "main.h"
#include "renderer.h"
#include "gameObject.h"

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

class ComputeShaderTest : GameObject
{
public:


	// GameObject を介して継承されました
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

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