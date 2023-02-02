#pragma once
#include "component_object.h"
#include "state_machine.h"
class CO_TitleUI :
    public ComponentObject
{
	class UserInterfaceComponent* _uiComponent;
public:
	virtual void InitInternal() ;
	virtual void UninitInternal();
	virtual void UpdateInternal();
	virtual void DrawInternal();
	virtual void DrawImguiInternal();
};

