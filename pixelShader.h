#pragma once
#include "resource.h"
class PixelShader :
    public Resource
{
    ID3D11PixelShader* m_PixelShader;
public:


    // Resource を介して継承されました
    virtual void Draw() override;

    virtual void Load(const char* FileName) override;

    virtual void Unload() override;

    inline static const std::string DEFAULT_PIXEL_SHADER = "vertexLightingPS.cso";
    inline static const std::string UNLIT_PIXEL_SHADER = "unlitTexturePS.cso";
    inline static const std::string RENDERING_TEXTURE_PS = "rendering_texture_ps.cso";

    inline static const std::string BLUR_PS = "post_effect_blur_ps.cso";
    inline static const std::string ENEMY_PS = "enemy_ps.cso";
};

