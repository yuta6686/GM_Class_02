#pragma once
#include "Component.h"
#include "ComputeShaderTestObject.h"

template <typename In,typename Out>
class ComputeShader
	: public Component
{
    std::string mFileName = "testCS.cso";

	ID3D11ComputeShader* mpComputeShader;
	ID3D11Buffer* mpBuff = nullptr;
	ID3D11Buffer* mppBuffResult = nullptr;
	ID3D11ShaderResourceView* mpBufSRV = nullptr;
	ID3D11UnorderedAccessView* mpBufResultUAV = nullptr;

    std::vector<In> mvBufInArray;
    int mNumElements = 128;

    Out* mpOutData = nullptr;
public:	
    Out* GetOutData()const { return mpOutData; }

    void SetInData(std::string filename,const std::vector<In>& in) { 
        mFileName = filename;
        Renderer::CreateComputeShader(&mpComputeShader, mFileName.c_str());

        mNumElements = in.size(); 
        mvBufInArray = in;
    }
	virtual void Update() override {

        //  コンピュートシェーダーへ入力時に使用するシェーダーリソースビューを作成する
        ComputeShaderTestObject::
        CreateSRVForStructuredBuffer(Renderer::GetDevice(), sizeof(In), mNumElements, &mvBufInArray[0], &mpBuff, &mpBufSRV);

        //  コンピュートシェーダーから出力時に使用するアンオーダードアクセスビューを作成
        ComputeShaderTestObject::
        CreateUAVForStructuredBuffer(Renderer::GetDevice(), sizeof(Out), mNumElements, NULL, &mppBuffResult, &mpBufResultUAV);

        //  コンピュートシェーダを実行する
        ComputeShaderTestObject::
        RunComputeShader(Renderer::GetDeviceContext(), mpComputeShader, mpBufSRV, mpBufResultUAV, mNumElements / 2, 1, 1);

        //  アンオーダードアクセスビューのバッファの内容をCPUから読み込み可能なバッファへコピーする
        ID3D11Buffer* debugbuf = ComputeShaderTestObject::CreateAndCopyToDebugBuf(Renderer::GetDevice(), Renderer::GetDeviceContext(), mppBuffResult);
        D3D11_MAPPED_SUBRESOURCE MappedResource;
        Renderer::GetDeviceContext()->Map(debugbuf, 0, D3D11_MAP_READ, 0, &MappedResource);
        mpOutData = reinterpret_cast<Out*>(MappedResource.pData);

        Renderer::GetDeviceContext()->Unmap(debugbuf, 0);

        debugbuf->Release();
    }

    virtual void Draw()override
    {

    }


	virtual void Init() override {
        
    }

	virtual void Uninit() override {
        mpComputeShader->Release();

        mpBuff->Release();
        mppBuffResult->Release();
        mpBufResultUAV->Release();
        mpBufSRV->Release();        
    }

};