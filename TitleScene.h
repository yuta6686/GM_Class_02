#pragma once
#include "scene.h"
class Transition;
class TitleScene :
    public Scene
{
    std::vector<int> a;
    Transition* m_Fade;
public:
    // Scene ����Čp������܂���
    virtual void Init() override;
    virtual void Update()override;
};

