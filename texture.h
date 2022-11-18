#pragma once
#include "main.h"
#include "resource.h"


class Texture :
    public Resource
{
private:
    ID3D11ShaderResourceView* m_Texture = NULL;
public:
    // Resource ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Draw() override;
    virtual void Load(const char* FileName) override;
    virtual void Unload() override;
};

