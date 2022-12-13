#include "CO_UI_Default.h"

void CO_UI_Default::Init()
{
    AddComponent<TransformInit>(COMLAYER_FIRST);

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    _uiComponent = AddComponent<UserInterfaceComponent>(COMLAYER_DRAW);

    ComponentObject::Init();
}

bool CO_UI_Default::SetUIInfo(UI_Information inf, D3DXVECTOR3 pos)
{
    if (_uiComponent == nullptr)return false;

    _uiComponent->SetUIInfo(inf);

    m_Position = pos;

    return true;
}

bool CO_UI_Default::ChangeWidthHeight(const D3DXVECTOR3& wh)
{
    if (_uiComponent == nullptr)return false;

    _uiComponent->SetWidthHeight(wh);

    return true;
}

bool CO_UI_Default::ChangeDeployIndex(const int& deploy)
{
    if (_uiComponent == nullptr)return false;

    _uiComponent->SetDeployIndex(deploy);

    return true;
}

bool CO_UI_Default::LoadTexture(std::string fname)
{
    if (_uiComponent == nullptr)return false;

    _uiComponent->LoadTexture(fname);

    return true;
}