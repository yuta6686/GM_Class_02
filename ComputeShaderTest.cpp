#include "ComputeShaderTest.h"
#include <io.h>

void ComputeShaderTest::Init()
{ 
    //���_��������� (Size�͎����Ō��߂�)
    VERTEX_3D_PARTICLE vertex[4];
    float Size = 100.0f;
    vertex[0].Position = D3DXVECTOR3(-Size, Size, 0.0f);
    vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
    vertex[1].Position = D3DXVECTOR3(Size, Size, 0.0f);
    vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
    vertex[2].Position = D3DXVECTOR3(-Size, -Size, 0.0f);
    vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
    vertex[3].Position = D3DXVECTOR3(Size, -Size, 0.0f);
    vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

    //�p�[�e�B�N����������(Amount�͍ő吔)
    int mParticleAmount = 100, Amount = 100;
    mparticle = new ParticleCompute[Amount];

    //�p�[�e�B�N���̎��������i�Œ肩�����_���Ƃ������ō��j
    for (int i = 0; i < Amount; i++) {
        mparticle[i].vel = D3DXVECTOR3(0, 1, 0); // ���x
        mparticle[i].life = 300.0f; // ���C�t�i�t���[���j
        mparticle[i].pos = D3DXVECTOR3(0, 0, 0); // ���W
    }

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(VERTEX_3D_PARTICLE) * 4;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = vertex;

    // ID3D11Device
    Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

    /*
    �o�b�t�@����
    D3D11_BUFFER_DESC�̐ݒ�F
 �@ desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = elementSize * count;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.StructureByteStride = elementSize;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    */
    Renderer::CreateStructuredBuffer(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpParticleBuffer);
    Renderer::CreateStructuredBuffer(sizeof(D3DXVECTOR3), (UINT)mParticleAmount, nullptr, &mpPositionBuffer);
    Renderer::CreateStructuredBuffer(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpResultBuffer);

    // SRV����
    Renderer::CreateBufferSRV(mpParticleBuffer, &mpParticleSRV);
    Renderer::CreateBufferSRV(mpPositionBuffer, &mpPositionSRV);
    // UAV����
    Renderer::CreateBufferUAV(mpResultBuffer, &mpResultUAV);

    // �R���s���[�g�V�F�[�_�[�쐬
    {
        FILE* file;
        long int fsize;

        file = fopen("ParticleCS", "rb");
        fsize = _filelength(_fileno(file));
        unsigned char* buffer = new unsigned char[fsize];
        fread(buffer, fsize, 1, file);
        fclose(file);

        Renderer::GetDevice()->CreateComputeShader(buffer, fsize, nullptr, &mComputeShader);

        delete[] buffer;
    }
}

void ComputeShaderTest::Uninit()
{
}

void ComputeShaderTest::Update()
{
}

void ComputeShaderTest::Draw()
{
}
