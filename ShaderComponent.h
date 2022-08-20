#pragma once
#include "gameObject.h"
#include "Component.h"

enum SHADER_TYPE {
    SHADER_DEFAULT,
    SHADER_UNLIT,
    SHADER_UNLIT_NO_MATERIAL,
    SHADER_TEST
};

class ShaderComponent :
    public Component
{
private:
    std::shared_ptr <VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;
    int m_ShaderType = SHADER_DEFAULT;
public:    
    ShaderComponent():m_ShaderType(SHADER_DEFAULT) {}
    ShaderComponent(const int& stype) :m_ShaderType(stype) {}


    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;
    virtual void DrawImgui()  override {};

    virtual void SetUnlitShader()
    {
        m_ShaderType = SHADER_UNLIT;
    }

    virtual void SetUnlitNoMaterialShader()
    {
        m_ShaderType = SHADER_UNLIT_NO_MATERIAL;
    }

    void SetTestShader()
    {
        m_ShaderType = SHADER_TEST;
    }
};

