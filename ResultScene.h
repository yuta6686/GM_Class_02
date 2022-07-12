#pragma once
#include "scene.h"
class Transition;
class ResultScene :
    public Scene
{
    Transition* m_FadeIn;
    Transition* m_FadeOut;
public:
    // Scene を介して継承されました
    virtual void Init() override;
    virtual void Update()override;
};

