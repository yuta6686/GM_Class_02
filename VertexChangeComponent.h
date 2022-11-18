#pragma once
#include "component.h"
class VertexChangeComponent :
    public Component
{
public:


    // Component ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override {};

    virtual void Uninit() override {};

    virtual void Update() override {};

    virtual void Draw() override {
        m_Parent->GetComponent<UserInterfaceComponent>()->ChangeVertexDraw();
    }

    virtual void DrawImgui() override {};

};

