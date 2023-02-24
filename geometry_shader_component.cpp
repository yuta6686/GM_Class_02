#include "stdafx.h"
#include "geometry_shader_component.h"

GeometryShaderComponent::GeometryShaderComponent()
	:_geometryShader(nullptr),
	_gShaderType(GSHADER_TYPE_TEST)
{
}

GeometryShaderComponent::GeometryShaderComponent(const int& type)
{
}

void GeometryShaderComponent::SetGeometryShaderType(const int& shaderType)
{
	_gShaderType = shaderType;

	Init();
}

void GeometryShaderComponent::Init()
{
	_geometryShader = 
		ResourceManager<GeometryShader>::GetResource(GeometryShader::GetFileNames()[GEOMETRY_SHADER_TYPE::GSHADER_TYPE_TEST]);
}

void GeometryShaderComponent::Uninit()
{
}

void GeometryShaderComponent::Update()
{
}

void GeometryShaderComponent::Draw()
{
	_geometryShader->Draw();
}

void GeometryShaderComponent::DrawImgui()
{
}
