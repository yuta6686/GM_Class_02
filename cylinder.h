#pragma once
#include "component_object.h"
class Cylinder :
    public ComponentObject
{
public:

    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

