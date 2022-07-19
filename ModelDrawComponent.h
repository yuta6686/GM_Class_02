#pragma once
#include "Component.h"
#include "model.h"
#include "ResourceManager.h"

class ModelDrawComponent :
    public Component
{
    std::shared_ptr<Model> m_Model;
    std::string m_SourcePath = "asset\\model\\M_otorii.obj";
public:
    void SetSourcePath(std::string path) {
        m_SourcePath = path;
    }

    ModelDrawComponent() {}
    ModelDrawComponent(std::string path) :m_SourcePath(path) {}

    // Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override 
    {
        m_Model =
            ResourceManger<Model>::GetResource(m_SourcePath.c_str());
    };

    virtual void Uninit() override {};

    virtual void Update() override {};

    virtual void Draw() override 
    {
        m_Model->Draw();
    };

};

