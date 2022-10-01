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

        //  �R���s���[�g�V�F�[�_�[�֓��͎��Ɏg�p����V�F�[�_�[���\�[�X�r���[���쐬����
        ComputeShaderTestObject::
        CreateSRVForStructuredBuffer(Renderer::GetDevice(), sizeof(In), mNumElements, &mvBufInArray[0], &mpBuff, &mpBufSRV);

        //  �R���s���[�g�V�F�[�_�[����o�͎��Ɏg�p����A���I�[�_�[�h�A�N�Z�X�r���[���쐬
        ComputeShaderTestObject::
        CreateUAVForStructuredBuffer(Renderer::GetDevice(), sizeof(Out), mNumElements, NULL, &mppBuffResult, &mpBufResultUAV);

        //  �R���s���[�g�V�F�[�_�����s����
        ComputeShaderTestObject::
        RunComputeShader(Renderer::GetDeviceContext(), mpComputeShader, mpBufSRV, mpBufResultUAV, mNumElements / 2, 1, 1);

        //  �A���I�[�_�[�h�A�N�Z�X�r���[�̃o�b�t�@�̓��e��CPU����ǂݍ��݉\�ȃo�b�t�@�փR�s�[����
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