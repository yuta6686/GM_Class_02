#pragma once
#include "Component.h"

class MatrixComponent :
    public Component
{
public:


    // Component ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

