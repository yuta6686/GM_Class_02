#include "CO_UI_Default.h"

void CO_UI_Default::Init()
{
    AddComponent<TransformInit>(COMLAYER_FIRST);

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    m_UIComponent = AddComponent<UserInterfaceComponent>(COMLAYER_DRAW);

    ComponentObject::Init();
}

bool CO_UI_Default::SetUIInfo(UI_Information inf, D3DXVECTOR3 pos)
{
    if (m_UIComponent == nullptr)return false;

    m_UIComponent->SetUIInfo(inf);

    m_Position = pos;

    return true;
}

bool CO_UI_Default::ChangeWidthHeight(const D3DXVECTOR3& wh)
{
    if (m_UIComponent == nullptr)return false;

    m_UIComponent->SetWidthHeight(wh);

    return true;
}

bool CO_UI_Default::ChangeDeployIndex(const int& deploy)
{
    if (m_UIComponent == nullptr)return false;

    m_UIComponent->SetDeployIndex(deploy);

    return true;
}

bool CO_UI_Default::LoadTexture(std::string fname)
{
    if (m_UIComponent == nullptr)return false;

    m_UIComponent->LoadTexture(fname);

    return true;
}