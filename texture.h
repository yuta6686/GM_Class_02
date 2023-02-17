#pragma once

#include "resource.h"


class Texture :
    public Resource
{
private:
    ShaderResourceView m_Texture;
public:
    // Resource ����Čp������܂���
    virtual void Draw() override;
    virtual void Load(const char* FileName) override;
    virtual void Unload() override;    
};

