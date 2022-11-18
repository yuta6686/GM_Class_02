#pragma once
#include "component.h"
#include "gameObject.h"
#include "model_draw_component.h"

class ModelColorChangeComponent :
    public Component
{
protected:
    D3DXCOLOR m_Diffuse = { 1.0f,1.0f,1.0f,1.0f };
    
public:

    virtual void Init() override {}
    virtual void Uninit() override {}
    virtual void Update() override {}
    virtual void Draw() override
    {
        m_Parent->GetComponent<ModelDrawComponent>()->SetDiffuse(m_Diffuse);
    }
    virtual void DrawImgui() override {
        ImGui::SliderFloat("Alpha", &m_Diffuse.a, 0.0f, 1.0f, "%.2f");
    }
};

