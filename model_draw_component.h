#pragma once
//  ---------------------------------------------------------
//  ModelDrawComponent [ModelDrawComponent.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - Modelï`âÊóp
//  ---------------------------------------------------------
#include "component.h"
#include "model.h"
#include "resource_manager.h"

class ModelDrawComponent :
    public Component
{
    std::shared_ptr<Model> m_Model;
    std::shared_ptr<Model_variable> m_Model_variable;
    std::string m_SourcePath = "asset\\model\\M_otorii.obj";

    bool m_IsVariable = false;    
public:
    void SetSourcePath(std::string path) {
        m_SourcePath = path;
    }

    void SetIsVariable(bool flag = true) {
        m_IsVariable = flag;
    }

    void SetDiffuse(D3DXCOLOR diff) { m_Model_variable->SetDiffuse(diff); }

    ModelDrawComponent() {}
    ModelDrawComponent(std::string path) :m_SourcePath(path) {}
    

    // Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override 
    {
        if (m_IsVariable) {
            m_Model_variable =
                ResourceManger<Model_variable>::GetResource(m_SourcePath.c_str());            
        }
        else
        {
            m_Model =
                ResourceManger<Model>::GetResource(m_SourcePath.c_str());
        }

    };

    virtual void Uninit() override {};

    virtual void Update() override {};

    virtual void Draw() override 
    {
        if (m_IsVariable) {
            Renderer::SetAlphaToCoverage(true);
            m_Model_variable->Draw();
            Renderer::SetAlphaToCoverage(false);
        }
        else
        {
            m_Model->Draw();            
        }
       
    };
    
    virtual void DrawImgui()  override {};

};

