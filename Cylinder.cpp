#include "cylinder.h"


void Cylinder::Init()
{		
	AddComponent<MatrixComponent>(COMLAYER_MATRIX);

	AddComponent<ModelDrawComponent>(COMLAYER_DRAW)->SetSourcePath("asset\\model\\drum.obj");

	AddComponent<TransformInit>(COMLAYER_FIRST);

	AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_DEFAULT);

	AddComponent<ImGuiComponent>(COMLAYER_SECOND);

	ComponentObject::Init();
}

void Cylinder::Uninit()
{
	ComponentObject::Uninit();
}

void Cylinder::Update()
{
	ComponentObject::Update();
}

void Cylinder::Draw()
{

	ComponentObject::Draw();
}

void Cylinder::DrawImgui()
{
	ComponentObject::DrawImgui();
}
