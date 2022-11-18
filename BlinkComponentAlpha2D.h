#pragma once
#include "component.h"
#include "UserInterfaceComponent.h"
#include "BlinkComponent.h"
class AlphaBlink2DComponent :
	public BlinkComponent
{
private:
	UserInterfaceComponent* m_UIComponent = nullptr;
public:
	virtual void Init() override {
		m_UIComponent = m_Parent->GetComponent<UserInterfaceComponent>();

		//	nullptr ��������킩��悤�ɁA�m�F�B�@��ŏ���
		m_UIComponent->m_Parent->GetPosition();
	}

	virtual void Update() override
	{
		BlinkComponent::Update();
		m_UIComponent->SetAlpha(m_BlinkValue);
	}

};

