#pragma once
#include "gameObject.h"
#include "ComponentObject.h"
class RenderingTexture :
    public ComponentObject
{
private:

public:
    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

