#pragma once
#include "scene.h"
class TitleScene :
    public Scene
{
    std::vector<int> a;
public:
    // Scene ����Čp������܂���
    virtual void Init() override;
    virtual void Update()override;
};

