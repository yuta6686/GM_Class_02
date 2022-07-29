#pragma once
#include "Component.h"
class VertexChangeComponent :
    public Component
{
public:


    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

