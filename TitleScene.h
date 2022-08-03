#pragma once
#include "scene.h"
#include "CO_3DPloygonTest.h"
class Transition;
class TitleScene :
    public Scene
{
    std::vector<int> a;
    Transition* m_Fade;
    std::vector<CO_3DPloygonTest*> m_SwitchToScenes;
public:
    // Scene を介して継承されました
    virtual void Init() override;
    virtual void Update()override;
};

