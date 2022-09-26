#include "ComputeShaderTest.h"
#include "camera.h"
#include "manager.h"
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
   //�p�[�e�B�N����������(Amount�͍ő吔)
    int Amount = 100;
    mParticleAmount = Amount;
    mparticle = new ParticleCompute[Amount];

    //�p�[�e�B�N���̎��������i�Œ肩�����_���Ƃ������ō��j
    for (int i = 0; i < mParticleAmount; i++) {
        mparticle[i].vel = MyMath::VEC3Random(-0.1f, 0.1f);
        mparticle[i].life = 300.0f; // ���C�t�i�t���[���j
        mparticle[i].pos = MyMath::VEC3Random(-100.0f, 100.0f);
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
    Renderer::CreateComputeShader(&mComputeShader, "ParticleCS.cso");
   
    //	�V�F�[�_������---------------------------------------
    m_VertexShader =
        ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
    m_PixelShader =
        ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());
}

void ComputeShaderTest::Uninit()
{
    mVertexBuffer->Release();

    mpParticleBuffer->Release();
    mpResultBuffer->Release();
    mpPositionBuffer->Release();
    mpParticleSRV->Release();
    mpPositionSRV->Release();

    mpResultUAV->Release();

    delete[] mparticle;
}

void ComputeShaderTest::Update()
{
    // �p�[�e�B�N���̎������o�b�t�@�ɓ����
    {
        D3D11_MAPPED_SUBRESOURCE subRes;
        Renderer::GetDeviceContext()->Map(mpParticleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
        ParticleCompute* pBufType = (ParticleCompute*)subRes.pData;
        memcpy(subRes.pData, mparticle, sizeof(ParticleCompute) * mParticleAmount);
        Renderer::GetDeviceContext()->Unmap(mpParticleBuffer, 0);
    }

    //�@�R���s���[�g�V�F�[�_�[���s
    ID3D11ShaderResourceView* pSRVs[1] = { mpParticleSRV };
    Renderer::GetDeviceContext()->CSSetShaderResources(0, 1, pSRVs);
    Renderer::GetDeviceContext()->CSSetShader(mComputeShader, nullptr, 0);
    Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &mpResultUAV, 0);
    Renderer::GetDeviceContext()->Dispatch(256, 1, 1);

    // �߂����v�Z���ʂ��o�b�t�@�ɓ����
    ID3D11Buffer* pBufDbg = Renderer::CreateAndCopyToDebugBuf(mpResultBuffer);
    D3D11_MAPPED_SUBRESOURCE subRes;
    Renderer::GetDeviceContext()->Map(pBufDbg, 0, D3D11_MAP_READ, 0, &subRes);
    ParticleCompute* pBufTypeParticle = (ParticleCompute*)subRes.pData;
    memcpy(mparticle, pBufTypeParticle, sizeof(ParticleCompute) * mParticleAmount);
    Renderer::GetDeviceContext()->Unmap(pBufDbg, 0);
    pBufDbg->Release();

    // ���W�����W�o�b�t�@�ɓ����(���_�V�F�[�_�[�Ŏg��)
    {
        Renderer::GetDeviceContext()->Map(mpPositionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
        D3DXVECTOR3* pBufType = (D3DXVECTOR3*)subRes.pData;
        for (int v = 0; v < mParticleAmount; v++) {
            pBufType[v] = mparticle[v].pos;
        }
    }
    Renderer::GetDeviceContext()->Unmap(mpPositionBuffer, 0);
}

void ComputeShaderTest::Draw()
{
    // �r���{�[�h
    Camera* camera = Manager::GetScene()->GetGameObject<Camera>();
    D3DXMATRIX view = camera->GetViewMatrix();
    D3DXMATRIX invView;
    D3DXMatrixInverse(&invView, NULL, &view);
    invView._41 = 0.0f;
    invView._42 = 0.0f;
    invView._43 = 0.0f;

    // ���[���h���W�A�X�P�[���Ȃǂ̏���
    D3DXMATRIX world, scale, trans;
    D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
    D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
    world = scale * invView * trans;
    Renderer::SetWorldMatrix(&world);

    // �C���v�b�g���C�A�E�g�ݒ�Ȃ�
    //Renderer::SetInputLayout(1);
    UINT stride = sizeof(VERTEX_3D_PARTICLE);
    UINT offset = 0;

    // VS�APS�V�F�[�_�[�ݒ�           
    m_VertexShader->Draw();
    m_PixelShader->Draw();

    // �`��
    Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    //Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture); // �e�N�X�`���ݒ�i����΁j
    //Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &mpPositionSRV); // VS�ɓ������W�ݒ�
    //Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //Renderer::GetDeviceContext()->DrawInstanced(4, mParticleAmount, 0, 0);

    m_Textures[0]->Draw();
    // �C���v�b�g���C�A�E�g�ݒ�
   //Renderer::SetInputLayout(0);
}
