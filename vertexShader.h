#pragma once
#include "resource.h"
#include "shader_include.h"

class VertexShader :
    public Resource
{
private:
    using DXVertexShader = ComPtr< ID3D11VertexShader>;
    using DXInputLayout = ComPtr< ID3D11InputLayout>;
    DXVertexShader m_VertexShader = nullptr;   
    DXInputLayout m_VertexLayout = nullptr;
public:
    // Resource を介して継承されました
    virtual void Draw() override;

    virtual void Load(const char* FileName) override;

    virtual void Unload() override;

    inline static std::map<SHADER_TYPE, std::string> GetFileNames() { return _fileNames; }
private:
    inline static const std::string SHADER_PASS = "shader\\";
    inline static const std::map<SHADER_TYPE, std::string> _fileNames = {
        {SHADER_TYPE::SHADER_DEFAULT,"vertexLightingVS.cso"},
        {SHADER_TYPE::SHADER_UNLIT,"unlitTextureVS.cso"},
        {SHADER_TYPE::SHADER_UNLIT_NO_MATERIAL,"unlitTextureNoMat.cso"},
        {SHADER_TYPE::SHADER_NOISE,"testVS.cso"},
        {SHADER_TYPE::SHADER_NOISE_CIRCLE,"noise_circle_vs.cso"},
        {SHADER_TYPE::SHADER_RENDERING_TEXTURE,"rendering_texture_vs.cso"},
        {SHADER_TYPE::SHADER_BLURX,"post_effect_blur_x_vs.cso"},
        {SHADER_TYPE::SHADER_BLURY,"post_effect_blur_y_vs.cso"},
        {SHADER_TYPE::SHADER_ENEMY,"enemy_vs.cso"},
        {SHADER_TYPE::SHADER_ENVIRONMENT_MAPPING,"env_mapping_vs.cso"},
        {SHADER_TYPE::SHADER_ENVIRONMENT_MAPPING_SELECT,"env_mapping_vs.cso"},
        {SHADER_TYPE::SHADER_LUMINANCE,"env_mapping_vs.cso"},
        {SHADER_TYPE::SHADER_PARTICLE,"unlitTextureVS.cso"},
        {SHADER_TYPE::SHADER_STEALTH,"StealthVS.cso"},
        {SHADER_TYPE::SHADER_BLOOM,"unlitTextureVS.cso"},
        {SHADER_TYPE::SHADER_DEPTH_OF_FIELD,"depth_of_field_vs.cso"}
    };    
    
};

