#pragma once
#include "Resource.h"

class VertexShader :
    public Resource
{
private:
    ID3D11VertexShader* m_VertexShader;   
    ID3D11InputLayout* m_VertexLayout;
public:
    // Resource ����Čp������܂���
    virtual void Draw() override;

    virtual void Load(const char* FileName) override;

    virtual void Unload() override;

};

