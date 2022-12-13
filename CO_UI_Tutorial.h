#pragma once
#include "component_object.h"
#include "user_interface_component.h"
#include "vertex_change_component.h"
class CO_UI_Tutorial :
    public ComponentObject
{
    UserInterfaceComponent* _uiComponent;
    CountComponent* m_Count;

    UI_Information m_UIinfo;
    
public:    
    std::string m_Name = "Tutorial";
    void SetColor(const D3DXVECTOR4& col) { _uiComponent->SetColor(col); }
    void SetTexture(const std::string& tex) { _uiComponent->LoadTexture(tex); }
    void SetUIComponentInfo(const UI_Information& uii) { 
        m_UIinfo = uii;
        _uiComponent->SetUIInfo(uii); 
    }
    void CountStart(bool in,
        const int& max,
        const int& delay)
    {
        m_Count->Start(in, max, delay);
    }
    virtual void Init()override;



    virtual void DrawImgui()override;
};

