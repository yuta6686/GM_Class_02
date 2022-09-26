#pragma once
#include "scene.h"

class DebugScene :
    public Scene
{
private:
    

public:
    // Scene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void Draw()override;

    inline static bool mbGameObject = false;
};

