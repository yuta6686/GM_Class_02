#pragma once
//  ---------------------------------------------------------
//  ModelDrawComponent [ModelDrawComponent.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - Modelï`âÊóp
//  ---------------------------------------------------------
#include "component.h"

class Model;
class Model_variable;
class ModelDrawComponent :
    public Component
{
    std::shared_ptr<Model> m_Model;
    std::shared_ptr<Model_variable> m_Model_variable;
    std::string m_SourcePath = "asset\\model\\M_otorii.obj";

    bool m_IsVariable = false;    
public:
    
    void SetSourcePath(std::string path);

    void SetIsVariable(bool flag = true);

    void SetDiffuse(D3DXCOLOR diff);

    ModelDrawComponent() {}
    ModelDrawComponent(std::string path) :m_SourcePath(path) {}
    

    // Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;

    virtual void Uninit() override {};

    virtual void Update() override {};

    virtual void Draw() override;

    virtual void DrawImgui()  override {};

};

