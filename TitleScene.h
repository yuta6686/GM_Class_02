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
    // Scene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void Update()override;
};

