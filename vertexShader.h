#pragma once
#include "resource.h"

class VertexShader :
    public Resource
{
private:
    ID3D11VertexShader* m_VertexShader = nullptr;   
    ID3D11InputLayout* m_VertexLayout = nullptr;
public:
    // Resource ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Draw() override;

    virtual void Load(const char* FileName) override;

    virtual void Unload() override;

    inline static const std::string DEFAULT_VERTEX_SHADER = "vertexLightingVS.cso";
    inline static const std::string UNLIT_VERTEX_SHADER = "unlitTextureVS.cso";
    inline static const std::string UNLIT_NO_MATERIAL_VERTEX_SHADER = "unlitTextureNoMat.cso";
    inline static const std::string RENDERING_TEXTURE_VS = "rendering_texture_vs.cso";
    inline static const std::string BLURX_VS = "post_effect_blur_x_vs.cso";
    inline static const std::string BLURY_VS = "post_effect_blur_y_vs.cso";
    inline static const std::string ENEMY_VS = "enemy_vs.cso";
private:
    
};

