#pragma once
#include "scene.h"
#include "MyImgui.h"

class DebugScene :
    public Scene
{
private:
    

public:
    // Scene を介して継承されました
    virtual void Init() override;
    virtual void Draw()override;

};

