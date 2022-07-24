#pragma once
#include "scene.h"
class Transition;
class TitleScene :
    public Scene
{
    std::vector<int> a;
    Transition* m_Fade;
public:
    // Scene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void Update()override;
};

