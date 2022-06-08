#pragma once
#include "Resource.h"
class PixelShader :
    public Resource
{
    ID3D11PixelShader* m_PixelShader;
public:


    // Resource ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Draw() override;

    virtual void Load(const char* FileName) override;

    virtual void Unload() override;

};

