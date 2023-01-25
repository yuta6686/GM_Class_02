#include "stdafx.h"
#include "co_stealth.h"
#include "shader_resource_view_component.h"

void co_stealth::InitInternal()
{
    AddComponent<TransformInit>(COMLAYER_FIRST)->SetInitPosScale({ 0.0f,5.0f,0.0f }, { 5.0f,5.0f,5.0f });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_TYPE::SHADER_STEALTH);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX);

    AddComponent<ShaderResourceViewComponent>(COMLAYER_DRAW)->SetRenderingTexture(2);

    auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\bow_red.obj");

    
}

void co_stealth::UninitInternal()
{
}

void co_stealth::UpdateInternal()
{
}

void co_stealth::DrawInternal()
{
}

void co_stealth::DrawImguiInternal()
{
}
