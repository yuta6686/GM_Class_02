#pragma once
#include "scene.h"
class TitleScene :
    public Scene
{
    std::vector<int> a;
public:
    // Scene を介して継承されました
    virtual void Init() override;
    virtual void Update()override;
};

