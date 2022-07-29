#include "MatrixComponent.h"
#include "gameObject.h"

void MatrixComponent::Init()
{
}

void MatrixComponent::Uninit()
{
}

void MatrixComponent::Update()
{
}

void MatrixComponent::Draw()
{
	if (m_Is2D) {
		Renderer::SetWorldViewProjection2D();
	}

	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale,
		m_Parent->GetScale().x,
		m_Parent->GetScale().y,
		m_Parent->GetScale().z);
	D3DXMatrixRotationYawPitchRoll(&rot,
		m_Parent->GetRotation().x,
		m_Parent->GetRotation().y,
		m_Parent->GetRotation().z);
	D3DXMatrixTranslation(&trans,
		m_Parent->GetPosition().x,
		m_Parent->GetPosition().y, 
		m_Parent->GetPosition().z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);
}
