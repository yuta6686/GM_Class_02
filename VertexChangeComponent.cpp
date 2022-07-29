#include "VertexChangeComponent.h"
#include "gameObject.h"
#include "UserInterfaceComponent.h"

void VertexChangeComponent::Init()
{
}

void VertexChangeComponent::Uninit()
{
}

void VertexChangeComponent::Update()
{
}

void VertexChangeComponent::Draw()
{
	m_Parent->GetComponent<UserInterfaceComponent>()->ChangeVertexDraw();
}

void VertexChangeComponent::DrawImgui()
{
}
