#include "stdafx.h"
#include "co_noise_circle.h"
#include "vertex_initialize.h"
#include "polygon3d_component.h"

void CO_NoiseCircle::InitInternal()
{
	const float scale = 50.0f;
	D3DXVECTOR3 Scale = { scale,scale,scale };
	D3DXVECTOR3 Position = { 0.0f,-7.0f,0.0f };
	AddComponent<TransformInit>(COMLAYER_FIRST)->SetInitPosScale(Position, Scale);
	auto polygon = AddComponent<Polygon3DComponent>(COMLAYER_DRAW);
	polygon->LoadTexture("asset\\texture\\field.jpg");
	polygon->SetIsVertical(false);


	AddComponent<MatrixComponent>(COMLAYER_MATRIX);
	AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_NOISE_CIRCLE);
	AddComponent<TextureComponent>(COMLAYER_SHADER)->SetTextureAndSlot("asset\\texture\\gradation.dds", 1);
	AddComponent<TextureComponent>(COMLAYER_SHADER)->SetTextureAndSlot("asset\\texture\\gradation_color1.png", 2);

	AddComponent<ImGuiComponent>(COMLAYER_DRAW)->SetIsUse(true);
}

void CO_NoiseCircle::UninitInternal()
{
}

void CO_NoiseCircle::UpdateInternal()
{
}

void CO_NoiseCircle::DrawInternal()
{

}

void CO_NoiseCircle::DrawImguiInternal()
{
	if (!MyImgui::_myFlag["Shader"])return;
	ImGui::SliderFloat("variable pad3", &Renderer::m_Valiable.pad3, 0.0f, 3.0f);
	
}
