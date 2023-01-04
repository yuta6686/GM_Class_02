//  ---------------------------------------------------------
//  MatrixComponent [MatrixComponent.cpp]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - Matrix (3D , 2D)
//  ---------------------------------------------------------
#include "matrix_component.h"
#include "gameObject.h"


void MatrixComponent::Init()
{
	m_Scene = Manager::GetScene();
	m_Camera = m_Scene->GetGameObject<Camera>();
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



	if (m_IsBillboard) {
		//	カメラのビューマトリクス取得				
		D3DXMATRIX view = m_Camera->GetViewMatrix();

		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view);	//	逆行列

		invView._41 =
			invView._42 =
			invView._43 = 0.0f;

		//マトリクス設定
		D3DXMATRIX world, scale, trans;
		D3DXMatrixScaling(&scale,
			m_Parent->GetScale().x,
			m_Parent->GetScale().y,
			m_Parent->GetScale().z);

		D3DXMatrixTranslation(&trans,
			m_Parent->GetPosition().x,
			m_Parent->GetPosition().y,
			m_Parent->GetPosition().z);

		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);

		return;
	}

	if (m_IsInvertXYRotate) {
		//マトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale,
			m_Parent->GetScale().x,
			m_Parent->GetScale().y,
			m_Parent->GetScale().z);		
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Parent->GetRotation().y,
			m_Parent->GetRotation().x,
			m_Parent->GetRotation().z);
		D3DXMatrixTranslation(&trans,
			m_Parent->GetPosition().x,
			m_Parent->GetPosition().y,
			m_Parent->GetPosition().z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);		
		return;
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

D3DXMATRIX MatrixComponent::GetWorldMatrix()
{
	//ワールドマトリクス設定
	D3DXMATRIX  scale, rot, trans;
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
	return scale * rot * trans;	
}
