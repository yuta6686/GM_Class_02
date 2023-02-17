#pragma once
#include "component_object.h"
class GeometryShaderComponentObject :
    public ComponentObject
{
public:
    virtual void Draw()override;
    virtual void InitInternal()override;
};

