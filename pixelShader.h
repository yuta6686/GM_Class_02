#pragma once
#include "resource.h"
class PixelShader :
    public Resource
{
    ID3D11PixelShader* m_PixelShader;
public:


    // Resource ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Draw() override;

    virtual void Load(const char* FileName) override;

    virtual void Unload() override;

    inline static const std::string DEFAULT_PIXEL_SHADER = "vertexLightingPS.cso";
    inline static const std::string UNLIT_PIXEL_SHADER = "unlitTexturePS.cso";
};

