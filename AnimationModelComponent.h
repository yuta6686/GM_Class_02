#pragma once

#include "Component.h"
#include "AnimationModel.h"
#include "ResourceManager.h"

class AnimationModelComponent :
    public Component
{
    std::shared_ptr<AnimationModel> m_Animation_Model;
    std::string m_SourcePath = "asset\\model\\M_otorii.obj";

    bool m_IsVariable = false;
    int mFrame = 0;
public:
    void SetSourcePath(std::string path) {
        m_SourcePath = path;
    }

    void SetIsVariable(bool flag = true) {
        m_IsVariable = flag;
    }

    //void SetDiffuse(D3DXCOLOR diff) { m_Animation_Model->SetDiffuse(diff); }

    AnimationModelComponent() {}
    AnimationModelComponent(std::string path) :m_SourcePath(path) {}


    // Component を介して継承されました
    virtual void Init() override
    {
        m_Animation_Model =
            ResourceManger<AnimationModel>::GetResource(m_SourcePath.c_str());

        mFrame = 0;
    };

    virtual void Uninit() override {};

    virtual void Update() override {
        m_Animation_Model->Update(mFrame);
        mFrame++;
    };

    virtual void Draw() override
    {
        m_Animation_Model->Draw();

    };

    virtual void DrawImgui()  override {};

};

