#include "blink_alpha2d_component.h"
#include "user_interface_component.h"
#include "gameObject.h"

void AlphaBlink2DComponent::Init() 
{
	m_UIComponent = m_Parent->GetComponent<UserInterfaceComponent>();

	//	nullptr がいたらわかるように、確認。　後で消せ
	m_UIComponent->m_Parent->GetPosition();
}

void AlphaBlink2DComponent::Update()
{
	BlinkComponent::Update();
	m_UIComponent->SetAlpha(m_BlinkValue);
}