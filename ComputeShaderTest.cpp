#include "ComputeShaderTest.h"
#include "camera.h"
#include "manager.h"
#include <io.h>

void ComputeShaderTest::Init()
{ 
    //頂点資料入れる (Sizeは自分で決める)
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

    //パーティクル資料生成(Amountは最大数)
   //パーティクル資料生成(Amountは最大数)
    int Amount = 100;
    mParticleAmount = Amount;
    mparticle = new ParticleCompute[Amount];

    //パーティクルの資料入れる（固定かランダムとか自分で作る）
    for (int i = 0; i < mParticleAmount; i++) {
        mparticle[i].vel = MyMath::VEC3Random(-0.1f, 0.1f);
        mparticle[i].life = 300.0f; // ライフ（フレーム）
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
    バッファ生成
    D3D11_BUFFER_DESCの設定：
 　 desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = elementSize * count;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.StructureByteStride = elementSize;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    */
    Renderer::CreateStructuredBuffer(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpParticleBuffer);
    Renderer::CreateStructuredBuffer(sizeof(D3DXVECTOR3), (UINT)mParticleAmount, nullptr, &mpPositionBuffer);
    Renderer::CreateStructuredBuffer(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpResultBuffer);

    // SRV生成
    Renderer::CreateBufferSRV(mpParticleBuffer, &mpParticleSRV);
    Renderer::CreateBufferSRV(mpPositionBuffer, &mpPositionSRV);
    // UAV生成
    Renderer::CreateBufferUAV(mpResultBuffer, &mpResultUAV);

    // コンピュートシェーダー作成
    Renderer::CreateComputeShader(&mComputeShader, "ParticleCS.cso");
   
    //	シェーダ初期化---------------------------------------
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
    // パーティクルの資料をバッファに入れる
    {
        D3D11_MAPPED_SUBRESOURCE subRes;
        Renderer::GetDeviceContext()->Map(mpParticleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
        ParticleCompute* pBufType = (ParticleCompute*)subRes.pData;
        memcpy(subRes.pData, mparticle, sizeof(ParticleCompute) * mParticleAmount);
        Renderer::GetDeviceContext()->Unmap(mpParticleBuffer, 0);
    }

    //　コンピュートシェーダー実行
    ID3D11ShaderResourceView* pSRVs[1] = { mpParticleSRV };
    Renderer::GetDeviceContext()->CSSetShaderResources(0, 1, pSRVs);
    Renderer::GetDeviceContext()->CSSetShader(mComputeShader, nullptr, 0);
    Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &mpResultUAV, 0);
    Renderer::GetDeviceContext()->Dispatch(256, 1, 1);

    // 戻った計算結果をバッファに入れる
    ID3D11Buffer* pBufDbg = Renderer::CreateAndCopyToDebugBuf(mpResultBuffer);
    D3D11_MAPPED_SUBRESOURCE subRes;
    Renderer::GetDeviceContext()->Map(pBufDbg, 0, D3D11_MAP_READ, 0, &subRes);
    ParticleCompute* pBufTypeParticle = (ParticleCompute*)subRes.pData;
    memcpy(mparticle, pBufTypeParticle, sizeof(ParticleCompute) * mParticleAmount);
    Renderer::GetDeviceContext()->Unmap(pBufDbg, 0);
    pBufDbg->Release();

    // 座標を座標バッファに入れる(頂点シェーダーで使う)
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
    // ビルボード
    Camera* camera = Manager::GetScene()->GetGameObject<Camera>();
    D3DXMATRIX view = camera->GetViewMatrix();
    D3DXMATRIX invView;
    D3DXMatrixInverse(&invView, NULL, &view);
    invView._41 = 0.0f;
    invView._42 = 0.0f;
    invView._43 = 0.0f;

    // ワールド座標、スケールなどの処理
    D3DXMATRIX world, scale, trans;
    D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
    D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
    world = scale * invView * trans;
    Renderer::SetWorldMatrix(&world);

    // インプットレイアウト設定など
    //Renderer::SetInputLayout(1);
    UINT stride = sizeof(VERTEX_3D_PARTICLE);
    UINT offset = 0;

    // VS、PSシェーダー設定           
    m_VertexShader->Draw();
    m_PixelShader->Draw();

    // 描画
    Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    //Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture); // テクスチャ設定（あれば）
    //Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &mpPositionSRV); // VSに入れる座標設定
    //Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //Renderer::GetDeviceContext()->DrawInstanced(4, mParticleAmount, 0, 0);

    m_Textures[0]->Draw();
    // インプットレイアウト設定
   //Renderer::SetInputLayout(0);
}
