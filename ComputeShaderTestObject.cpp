#include "ComputeShaderTestObject.h"

void ComputeShaderTestObject::Init()
{    
    m_TypeName = "ComputeShaderTestObject";

	Renderer::CreateComputeShader(&mpComputeShader, "testCS.cso");

    //  入力用バッファに初期値を設定
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        mvBufInArray[i].i = i;
        mvBufInArray[i].f = static_cast<float>(NUM_ELEMENTS - 1 - i);
    }
}

void ComputeShaderTestObject::Uninit()
{
	
    mpBuff->Release();
    mppBuffResult->Release();
    mpBufResultUAV->Release();
    mpBufSRV->Release();
    
    mpComputeShader->Release();
}

void ComputeShaderTestObject::Update()
{
   

    //  コンピュートシェーダーへ入力時に使用するシェーダーリソースビューを作成する
    CreateSRVForStructuredBuffer(Renderer::GetDevice(), sizeof(BUFIN_TYPE), NUM_ELEMENTS, &mvBufInArray[0], &mpBuff, &mpBufSRV);

    //  コンピュートシェーダーから出力時に使用するアンオーダードアクセスビューを作成
    CreateUAVForStructuredBuffer(Renderer::GetDevice(), sizeof(BUFOUT_TYPE), NUM_ELEMENTS, NULL, &mppBuffResult, &mpBufResultUAV);

    //  コンピュートシェーダを実行する
    RunComputeShader(Renderer::GetDeviceContext(), mpComputeShader, mpBufSRV, mpBufResultUAV, NUM_ELEMENTS / 2, 1, 1);

    //  アンオーダードアクセスビューのバッファの内容をCPUから読み込み可能なバッファへコピーする
    ID3D11Buffer* debugbuf = CreateAndCopyToDebugBuf(Renderer::GetDevice(), Renderer::GetDeviceContext(), mppBuffResult);
    D3D11_MAPPED_SUBRESOURCE MappedResource;
    Renderer::GetDeviceContext()->Map(debugbuf, 0, D3D11_MAP_READ, 0, &MappedResource);
    mpOutData = reinterpret_cast<BUFOUT_TYPE*>(MappedResource.pData);


   

    Renderer::GetDeviceContext()->Unmap(debugbuf, 0);

    debugbuf->Release();
}

void ComputeShaderTestObject::Draw()
{
}

void ComputeShaderTestObject::DrawImgui()
{
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        ImGui::Text("%d + %d = %d", i, NUM_ELEMENTS - 1 - i, mpOutData[i]);
        //printf("%d + %d = %d", i, NUM_ELEMENTS - 1 - i, mpOutData[i].i);
    }
}

// コンピュートシェーダーへの入力時に使用するシェーダーリソースビューを作成する
HRESULT ComputeShaderTestObject::CreateSRVForStructuredBuffer(ID3D11Device* pD3DDevice
    , UINT uElementSize
    , UINT uCount
    , VOID* pInitData
    , ID3D11Buffer** ppBuf
    , ID3D11ShaderResourceView** ppSRVOut
)
{
    HRESULT hr = E_FAIL;

    *ppBuf = NULL;
    *ppSRVOut = NULL;

    // 構造化バッファーを作成する

    D3D11_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
    BufferDesc.BindFlags =
        D3D11_BIND_UNORDERED_ACCESS |                               // アンオーダード アクセス リソースをバインドする
        D3D11_BIND_SHADER_RESOURCE;                                 // バッファーをシェーダー ステージにバインドする
    BufferDesc.ByteWidth = uElementSize * uCount;                  // バッファサイズ
    BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;  // 構造化バッファーとしてリソースを作成する
    BufferDesc.StructureByteStride = uElementSize;                 // 構造化バッファーのサイズ (バイト単位)

    // 初期値を設定
    if (pInitData)
    {
        D3D11_SUBRESOURCE_DATA InitData;
        InitData.pSysMem = pInitData;
        hr = pD3DDevice->CreateBuffer(&BufferDesc, &InitData, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }
    // 初期値なしで領域のみ確保する
    else
    {
        hr = pD3DDevice->CreateBuffer(&BufferDesc, NULL, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }

    // 構造化バッファーからシェーダーリソースビューを作成する

    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
    ZeroMemory(&SRVDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;   // 拡張されたバッファーであることを指定する
    SRVDesc.BufferEx.FirstElement = 0;
    SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
    SRVDesc.BufferEx.NumElements = uCount;                  // リソース内の要素の数

    // 構造化バッファーをもとにシェーダーリソースビューを作成する
    hr = pD3DDevice->CreateShaderResourceView(*ppBuf, &SRVDesc, ppSRVOut);
    if (FAILED(hr))
        goto EXIT;

    hr = S_OK;
EXIT:
    return hr;
}

// コンピュートシェーダーからの出力時に使用するアンオーダードアクセスビューを作成する
HRESULT ComputeShaderTestObject::CreateUAVForStructuredBuffer(ID3D11Device* pD3DDevice
    , UINT uElementSize
    , UINT uCount
    , VOID* pInitData
    , ID3D11Buffer** ppBuf
    , ID3D11UnorderedAccessView** ppUAVOut
)
{
    HRESULT hr = E_FAIL;

    *ppBuf = NULL;
    *ppUAVOut = NULL;

    // 構造化バッファーを作成する

    D3D11_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
    BufferDesc.BindFlags =
        D3D11_BIND_UNORDERED_ACCESS |                               // アンオーダード アクセス リソースをバインドする
        D3D11_BIND_SHADER_RESOURCE;                                 // バッファーをシェーダー ステージにバインドする
    BufferDesc.ByteWidth = uElementSize * uCount;                  // バッファサイズ
    BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;  // 構造化バッファーとしてリソースを作成する
    BufferDesc.StructureByteStride = uElementSize;                 // 構造化バッファーのサイズ (バイト単位)

    // 初期値を設定
    if (pInitData)
    {
        D3D11_SUBRESOURCE_DATA InitData;
        InitData.pSysMem = pInitData;
        hr = pD3DDevice->CreateBuffer(&BufferDesc, &InitData, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }
    // 初期値なしで領域のみ確保する
    else
    {
        hr = pD3DDevice->CreateBuffer(&BufferDesc, NULL, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }

    // 構造化バッファーからアンオーダードアクセスビューを作成する

    D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
    ZeroMemory(&UAVDesc, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
    UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;   // バッファーであることを指定する
    UAVDesc.Buffer.FirstElement = 0;
    UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
    UAVDesc.Buffer.NumElements = uCount;                  // リソース内の要素の数

    // 構造化バッファーをもとにアンオーダード アクセス ビューを作成する
    hr = pD3DDevice->CreateUnorderedAccessView(*ppBuf, &UAVDesc, ppUAVOut);
    if (FAILED(hr))
        goto EXIT;

    hr = S_OK;
EXIT:
    return hr;
}

// コンピュートシェーダーを実行する
void ComputeShaderTestObject::RunComputeShader(ID3D11DeviceContext* pD3DDeviceContext
    , ID3D11ComputeShader* pComputeShader
    , ID3D11ShaderResourceView* pBufSRV         // 入力用
    , ID3D11UnorderedAccessView* pBufResultUAV  // 出力用
    , UINT X
    , UINT Y
    , UINT Z
)
{
    pD3DDeviceContext->CSSetShader(pComputeShader, NULL, 0);

    // シェーダーリソースビューをコンピュートシェーダーに設定
    pD3DDeviceContext->CSSetShaderResources(0, 1, &pBufSRV);

    // アンオーダードアクセスビューをコンピュートシェーダーに設定
    pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, &pBufResultUAV, NULL);

    // コンピュートシェーダーを実行する。いまいちわかってない
    pD3DDeviceContext->Dispatch(X, Y, Z);

    pD3DDeviceContext->CSSetShader(NULL, NULL, 0);

    ID3D11UnorderedAccessView* ppUAViewNULL[1] = { NULL };
    pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);

    ID3D11ShaderResourceView* ppSRVNULL[2] = { NULL, NULL };
    pD3DDeviceContext->CSSetShaderResources(0, 2, ppSRVNULL);

    ID3D11Buffer* ppCBNULL[1] = { NULL };
    pD3DDeviceContext->CSSetConstantBuffers(0, 1, ppCBNULL);
}

// アンオーダードアクセスビューのバッファの内容を CPU から読み込み可能なバッファへコピーする
ID3D11Buffer* ComputeShaderTestObject::CreateAndCopyToDebugBuf(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pD3DDeviceContext, ID3D11Buffer* pBuffer)
{
    ID3D11Buffer* debugbuf = NULL;

    D3D11_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
    pBuffer->GetDesc(&BufferDesc);
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;  // CPU から読み込みできるように設定する
    BufferDesc.Usage = D3D11_USAGE_STAGING;             // GPU から CPU へのデータ転送 (コピー) をサポートするリソース
    BufferDesc.BindFlags = 0;
    BufferDesc.MiscFlags = 0;
    if (FAILED(pD3DDevice->CreateBuffer(&BufferDesc, NULL, &debugbuf)))
        goto EXIT;

    pD3DDeviceContext->CopyResource(debugbuf, pBuffer);

EXIT:
    return debugbuf;
}