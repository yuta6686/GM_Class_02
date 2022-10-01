#include "ComputeShaderTestObject.h"

void ComputeShaderTestObject::Init()
{    
    m_TypeName = "ComputeShaderTestObject";

	Renderer::CreateComputeShader(&mpComputeShader, "testCS.cso");

    //  ���͗p�o�b�t�@�ɏ����l��ݒ�
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
   

    //  �R���s���[�g�V�F�[�_�[�֓��͎��Ɏg�p����V�F�[�_�[���\�[�X�r���[���쐬����
    CreateSRVForStructuredBuffer(Renderer::GetDevice(), sizeof(BUFIN_TYPE), NUM_ELEMENTS, &mvBufInArray[0], &mpBuff, &mpBufSRV);

    //  �R���s���[�g�V�F�[�_�[����o�͎��Ɏg�p����A���I�[�_�[�h�A�N�Z�X�r���[���쐬
    CreateUAVForStructuredBuffer(Renderer::GetDevice(), sizeof(BUFOUT_TYPE), NUM_ELEMENTS, NULL, &mppBuffResult, &mpBufResultUAV);

    //  �R���s���[�g�V�F�[�_�����s����
    RunComputeShader(Renderer::GetDeviceContext(), mpComputeShader, mpBufSRV, mpBufResultUAV, NUM_ELEMENTS / 2, 1, 1);

    //  �A���I�[�_�[�h�A�N�Z�X�r���[�̃o�b�t�@�̓��e��CPU����ǂݍ��݉\�ȃo�b�t�@�փR�s�[����
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

// �R���s���[�g�V�F�[�_�[�ւ̓��͎��Ɏg�p����V�F�[�_�[���\�[�X�r���[���쐬����
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

    // �\�����o�b�t�@�[���쐬����

    D3D11_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
    BufferDesc.BindFlags =
        D3D11_BIND_UNORDERED_ACCESS |                               // �A���I�[�_�[�h �A�N�Z�X ���\�[�X���o�C���h����
        D3D11_BIND_SHADER_RESOURCE;                                 // �o�b�t�@�[���V�F�[�_�[ �X�e�[�W�Ƀo�C���h����
    BufferDesc.ByteWidth = uElementSize * uCount;                  // �o�b�t�@�T�C�Y
    BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;  // �\�����o�b�t�@�[�Ƃ��ă��\�[�X���쐬����
    BufferDesc.StructureByteStride = uElementSize;                 // �\�����o�b�t�@�[�̃T�C�Y (�o�C�g�P��)

    // �����l��ݒ�
    if (pInitData)
    {
        D3D11_SUBRESOURCE_DATA InitData;
        InitData.pSysMem = pInitData;
        hr = pD3DDevice->CreateBuffer(&BufferDesc, &InitData, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }
    // �����l�Ȃ��ŗ̈�̂݊m�ۂ���
    else
    {
        hr = pD3DDevice->CreateBuffer(&BufferDesc, NULL, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }

    // �\�����o�b�t�@�[����V�F�[�_�[���\�[�X�r���[���쐬����

    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
    ZeroMemory(&SRVDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;   // �g�����ꂽ�o�b�t�@�[�ł��邱�Ƃ��w�肷��
    SRVDesc.BufferEx.FirstElement = 0;
    SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
    SRVDesc.BufferEx.NumElements = uCount;                  // ���\�[�X���̗v�f�̐�

    // �\�����o�b�t�@�[�����ƂɃV�F�[�_�[���\�[�X�r���[���쐬����
    hr = pD3DDevice->CreateShaderResourceView(*ppBuf, &SRVDesc, ppSRVOut);
    if (FAILED(hr))
        goto EXIT;

    hr = S_OK;
EXIT:
    return hr;
}

// �R���s���[�g�V�F�[�_�[����̏o�͎��Ɏg�p����A���I�[�_�[�h�A�N�Z�X�r���[���쐬����
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

    // �\�����o�b�t�@�[���쐬����

    D3D11_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
    BufferDesc.BindFlags =
        D3D11_BIND_UNORDERED_ACCESS |                               // �A���I�[�_�[�h �A�N�Z�X ���\�[�X���o�C���h����
        D3D11_BIND_SHADER_RESOURCE;                                 // �o�b�t�@�[���V�F�[�_�[ �X�e�[�W�Ƀo�C���h����
    BufferDesc.ByteWidth = uElementSize * uCount;                  // �o�b�t�@�T�C�Y
    BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;  // �\�����o�b�t�@�[�Ƃ��ă��\�[�X���쐬����
    BufferDesc.StructureByteStride = uElementSize;                 // �\�����o�b�t�@�[�̃T�C�Y (�o�C�g�P��)

    // �����l��ݒ�
    if (pInitData)
    {
        D3D11_SUBRESOURCE_DATA InitData;
        InitData.pSysMem = pInitData;
        hr = pD3DDevice->CreateBuffer(&BufferDesc, &InitData, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }
    // �����l�Ȃ��ŗ̈�̂݊m�ۂ���
    else
    {
        hr = pD3DDevice->CreateBuffer(&BufferDesc, NULL, ppBuf);
        if (FAILED(hr))
            goto EXIT;
    }

    // �\�����o�b�t�@�[����A���I�[�_�[�h�A�N�Z�X�r���[���쐬����

    D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
    ZeroMemory(&UAVDesc, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
    UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;   // �o�b�t�@�[�ł��邱�Ƃ��w�肷��
    UAVDesc.Buffer.FirstElement = 0;
    UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
    UAVDesc.Buffer.NumElements = uCount;                  // ���\�[�X���̗v�f�̐�

    // �\�����o�b�t�@�[�����ƂɃA���I�[�_�[�h �A�N�Z�X �r���[���쐬����
    hr = pD3DDevice->CreateUnorderedAccessView(*ppBuf, &UAVDesc, ppUAVOut);
    if (FAILED(hr))
        goto EXIT;

    hr = S_OK;
EXIT:
    return hr;
}

// �R���s���[�g�V�F�[�_�[�����s����
void ComputeShaderTestObject::RunComputeShader(ID3D11DeviceContext* pD3DDeviceContext
    , ID3D11ComputeShader* pComputeShader
    , ID3D11ShaderResourceView* pBufSRV         // ���͗p
    , ID3D11UnorderedAccessView* pBufResultUAV  // �o�͗p
    , UINT X
    , UINT Y
    , UINT Z
)
{
    pD3DDeviceContext->CSSetShader(pComputeShader, NULL, 0);

    // �V�F�[�_�[���\�[�X�r���[���R���s���[�g�V�F�[�_�[�ɐݒ�
    pD3DDeviceContext->CSSetShaderResources(0, 1, &pBufSRV);

    // �A���I�[�_�[�h�A�N�Z�X�r���[���R���s���[�g�V�F�[�_�[�ɐݒ�
    pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, &pBufResultUAV, NULL);

    // �R���s���[�g�V�F�[�_�[�����s����B���܂����킩���ĂȂ�
    pD3DDeviceContext->Dispatch(X, Y, Z);

    pD3DDeviceContext->CSSetShader(NULL, NULL, 0);

    ID3D11UnorderedAccessView* ppUAViewNULL[1] = { NULL };
    pD3DDeviceContext->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);

    ID3D11ShaderResourceView* ppSRVNULL[2] = { NULL, NULL };
    pD3DDeviceContext->CSSetShaderResources(0, 2, ppSRVNULL);

    ID3D11Buffer* ppCBNULL[1] = { NULL };
    pD3DDeviceContext->CSSetConstantBuffers(0, 1, ppCBNULL);
}

// �A���I�[�_�[�h�A�N�Z�X�r���[�̃o�b�t�@�̓��e�� CPU ����ǂݍ��݉\�ȃo�b�t�@�փR�s�[����
ID3D11Buffer* ComputeShaderTestObject::CreateAndCopyToDebugBuf(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pD3DDeviceContext, ID3D11Buffer* pBuffer)
{
    ID3D11Buffer* debugbuf = NULL;

    D3D11_BUFFER_DESC BufferDesc;
    ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
    pBuffer->GetDesc(&BufferDesc);
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;  // CPU ����ǂݍ��݂ł���悤�ɐݒ肷��
    BufferDesc.Usage = D3D11_USAGE_STAGING;             // GPU ���� CPU �ւ̃f�[�^�]�� (�R�s�[) ���T�|�[�g���郊�\�[�X
    BufferDesc.BindFlags = 0;
    BufferDesc.MiscFlags = 0;
    if (FAILED(pD3DDevice->CreateBuffer(&BufferDesc, NULL, &debugbuf)))
        goto EXIT;

    pD3DDeviceContext->CopyResource(debugbuf, pBuffer);

EXIT:
    return debugbuf;
}