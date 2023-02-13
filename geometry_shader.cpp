#include "stdafx.h"
#include "geometry_shader.h"

void GeometryShader::Draw()
{
	Renderer::GetDeviceContext()->GSSetShader(_geometryShader, nullptr, 0);
}

void GeometryShader::Load(const char* FileName)
{
	Renderer::CreateGeometryShader(&_geometryShader, FileName);
}

void GeometryShader::Unload()
{
	if (_geometryShader) 
	{
		_geometryShader->Release();
		_geometryShader = nullptr;
	}
}
