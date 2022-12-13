#pragma once
//  ---------------------------------------------------------
//  ShaderComponent [ShaderComponent.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - �V�F�[�_�p�R���|�[�l���g
// 
//	- ShaderType�ŕς��
//  ---------------------------------------------------------
#include "gameObject.h"
#include "component.h"


class ShaderComponent :
    public Component
{
private:
    std::shared_ptr <VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;
    int m_ShaderType = SHADER_DEFAULT;
    std::string _fileNameVS;
    std::string _fileNamePS;
public:    
    ShaderComponent():m_ShaderType(SHADER_DEFAULT) {}
    ShaderComponent(const int& stype) :m_ShaderType(stype) {}


    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;
    virtual void DrawImgui()  override {};

    void SetShaderType(const int& shaderType)
    {
        m_ShaderType = shaderType;
    }
};

