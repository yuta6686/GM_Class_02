#include "stdafx.h"
#include "shader_resource_view_component.h"

void ShaderResourceViewComponent::Init()
{
}

void ShaderResourceViewComponent::Uninit()
{
}

void ShaderResourceViewComponent::Update()
{
}

void ShaderResourceViewComponent::Draw()
{
	if (_renderingTexture)
	{
		Renderer::SetRenderTexture(false,_slot);
		return;
	}

	if (!_srv)return;

	Renderer::GetDeviceContext()->PSSetShaderResources(_slot, 1, _srv.GetAddressOf());
}

void ShaderResourceViewComponent::DrawImgui()
{
}

void ShaderResourceViewComponent::SetSRV(UINT slot,ShaderResourceView srv)
{
	_srv = srv;
	_slot = slot;
}

void ShaderResourceViewComponent::SetRenderingTexture(UINT slot)
{
	_renderingTexture = true;
	_slot = slot;
}
