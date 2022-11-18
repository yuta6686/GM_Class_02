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

		//	nullptr がいたらわかるように、確認。　後で消せ
		m_UIComponent->m_Parent->GetPosition();
	}

	virtual void Update() override
	{
		BlinkComponent::Update();
		m_UIComponent->SetAlpha(m_BlinkValue);
	}

};

