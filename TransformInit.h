#pragma once
#include "gameObject.h"
#include "Component.h"
class TransformInit :
    public Component
{
    
public:
    // Component ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override 
    {
        m_Parent->SetPosition({ 0.0f,0.0f,0.0f });
        m_Parent->SetRotation({ 0.0f,0.0f,0.0f });
        m_Parent->SetScale({ 1.0f,1.0f,1.0f });
    };
    virtual void Uninit() override {};
    virtual void Update() override {};
    virtual void Draw() override {};
    virtual void DrawImgui()  override {};
};

