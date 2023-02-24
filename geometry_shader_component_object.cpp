#include "stdafx.h"
#include "geometry_shader_component_object.h"

void GeometryShaderComponentObject::Draw()
{
	ComponentObject::Draw();
	
	Renderer::GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);
}

void GeometryShaderComponentObject::InitInternal()
{
	AddComponent<TransformInit>(COMLAYER_SECOND);

	AddComponent<MatrixComponent>(COMLAYER_MATRIX);

	AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

	AddComponent<GeometryShaderComponent>(COMLAYER_SHADER)->SetGeometryShaderType(GSHADER_TYPE_TEST);
}

