#pragma once
#include "gameObject.h"

struct BUFIN_TYPE
{
    D3DXVECTOR3 pos;
    float f;
    int status;
};

struct BUFOUT_TYPE
{
    int i;
    int status;
};
class ComputeShaderTestObject :
    public GameObject
{
private:
    inline static const UINT NUM_ELEMENTS = 128;

    HRESULT mhr = E_FAIL;

    ID3D11ComputeShader* mpComputeShader = nullptr;
    ID3D11Buffer* mpBuff = nullptr;
    ID3D11Buffer* mppBuffResult = nullptr;
    ID3D11ShaderResourceView* mpBufSRV = nullptr;
    ID3D11UnorderedAccessView* mpBufResultUAV = nullptr;
    
    BUFIN_TYPE mvBufInArray[NUM_ELEMENTS];


    BUFOUT_TYPE* mpOutData;

public:
    static HRESULT CreateSRVForStructuredBuffer(ID3D11Device* pD3DDevice
        , UINT uElementSize
        , UINT uCount
        , VOID* pInitData
        , ID3D11Buffer** ppBuf
        , ID3D11ShaderResourceView** ppSRVOut
    );

    static HRESULT CreateUAVForStructuredBuffer(ID3D11Device* pD3DDevice
        , UINT uElementSize
        , UINT uCount
        , VOID* pInitData
        , ID3D11Buffer** ppBuf
        , ID3D11UnorderedAccessView** ppUAVOut
    );
    // コンピュートシェーダーを実行する
    static void RunComputeShader(ID3D11DeviceContext* pD3DDeviceContext
        , ID3D11ComputeShader* pComputeShader
        , ID3D11ShaderResourceView* pBufSRV         // 入力用
        , ID3D11UnorderedAccessView* pBufResultUAV  // 出力用
        , UINT X
        , UINT Y
        , UINT Z        
    );

    static ID3D11Buffer* CreateAndCopyToDebugBuf(ID3D11Device* pD3DDevice,
        ID3D11DeviceContext* pD3DDeviceContext,
        ID3D11Buffer* pBuffer);
public:
    // GameObject を介して継承されました
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui()override;
};

