#pragma once
#include "Resource.h"

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
private:
    
};

