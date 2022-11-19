#pragma once
#include "component_object.h"
#include "user_interface_component.h"


class CO_UI_Default :
    public ComponentObject
{
private:
    UserInterfaceComponent* m_UIComponent;
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        m_UIComponent = AddComponent<UserInterfaceComponent>(COMLAYER_DRAW);

        ComponentObject::Init();
    }
    bool SetUIInfo(UI_Information inf)
    {
        if (m_UIComponent == nullptr)return false;

        m_UIComponent->SetUIInfo(inf);        

        return true;
    }

    bool SetUIInfo(UI_Information inf, D3DXVECTOR3 pos)
    {
        if (m_UIComponent == nullptr)return false;

        m_UIComponent->SetUIInfo(inf);

        m_Position = pos;

        return true;
    }

    bool ChangeWidthHeight(const D3DXVECTOR3& wh)
    {
        if (m_UIComponent == nullptr)return false;

        m_UIComponent->SetWidthHeight(wh);

        return true;
    }

    bool ChangeDeployIndex(const int& deploy)
    {
        if (m_UIComponent == nullptr)return false;

        m_UIComponent->SetDeployIndex(deploy);

        return true;
    }

    bool LoadTexture(std::string fname) {
        if (m_UIComponent == nullptr)return false;

        m_UIComponent->LoadTexture(fname);

        return true;
    }
};

