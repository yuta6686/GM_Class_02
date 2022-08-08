#pragma once
#include "Component.h"
class TextureComponent :
    public Component
{
public:    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

