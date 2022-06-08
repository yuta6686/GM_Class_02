#pragma once
#include "main.h"
#include "Resource.h"


class Texture :
    public Resource
{
private:
    ID3D11ShaderResourceView* m_Texture = NULL;
public:
    // Resource を介して継承されました
    virtual void Draw() override;
    virtual void Load(const char* FileName) override;
    virtual void Unload() override;
};

