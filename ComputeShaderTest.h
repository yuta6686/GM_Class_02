#pragma once
#include "main.h"
#include "renderer.h"
#include "gameObject.h"

// �p�[�e�B�N���p���_���C�A�E�g
struct VERTEX_3D_PARTICLE
{
	D3DXVECTOR3 Position;
	D3DXVECTOR2 TexCoord;
};
//����g���p�[�e�B�N���̎�����
struct ParticleCompute {
	// ���W
	D3DXVECTOR3 pos;
	// ���x
	D3DXVECTOR3 vel;
	// ���C�t
	float life;
};

class ComputeShaderTest : GameObject
{
public:


	// GameObject ����Čp������܂���
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	// �R���s���[�g�V�F�[�_�[
	ID3D11ComputeShader* mComputeShader;
	// �p�[�e�B�N��
	ParticleCompute* mparticle;
	// �o�b�t�@
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