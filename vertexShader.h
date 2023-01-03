#pragma once
#include "resource.h"
#include "shader_include.h"

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

    inline static std::map<SHADER_TYPE, std::string> GetFileNames() { return _fileNames; }
private:
    inline static const std::map<SHADER_TYPE, std::string> _fileNames = {
        {SHADER_TYPE::SHADER_DEFAULT,"vertexLightingVS.cso"},
        {SHADER_TYPE::SHADER_UNLIT,"unlitTextureVS.cso"},
        {SHADER_TYPE::SHADER_UNLIT_NO_MATERIAL,"unlitTextureNoMat.cso"},
        {SHADER_TYPE::SHADER_TEST,"testVS.cso"},
        {SHADER_TYPE::SHADER_RENDERING_TEXTURE,"rendering_texture_vs.cso"},
        {SHADER_TYPE::SHADER_BLURX,"post_effect_blur_x_vs.cso"},
        {SHADER_TYPE::SHADER_BLURY,"post_effect_blur_y_vs.cso"},
        {SHADER_TYPE::SHADER_ENEMY,"enemy_vs.cso"},
        {SHADER_TYPE::SHADER_ENVIRONMENT_MAPPING,"env_mapping_vs.cso"},
        {SHADER_TYPE::SHADER_ENVIRONMENT_MAPPING_SELECT,"env_mapping_vs.cso"},
    };    
    
};

