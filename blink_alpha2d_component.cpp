#include "blink_alpha2d_component.h"
#include "user_interface_component.h"
#include "gameObject.h"

void AlphaBlink2DComponent::Init() 
{
	_uiComponent = m_Parent->GetComponent<UserInterfaceComponent>();

	//	nullptr ��������킩��悤�ɁA�m�F�B�@��ŏ���
	_uiComponent->m_Parent->GetPosition();
}

void AlphaBlink2DComponent::Update()
{
	BlinkComponent::Update();
	_uiComponent->SetAlpha(m_BlinkValue);
}