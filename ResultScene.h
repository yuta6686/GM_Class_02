#pragma once
#include "scene.h"
class ResultScene :
    public Scene
{
public:
    // Scene を介して継承されました
    virtual void Init() override;
};

