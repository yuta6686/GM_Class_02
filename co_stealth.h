#pragma once
#include "component_object.h"
class co_stealth :
    public ComponentObject
{
public:
	virtual void InitInternal();
	virtual void UninitInternal();
	virtual void UpdateInternal();
	virtual void DrawInternal();
	virtual void DrawImguiInternal();
};

