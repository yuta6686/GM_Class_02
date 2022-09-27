#pragma once

#include "Component.h"
#include "AnimationModel.h"
#include "ResourceManager.h"

class AnimationModelComponent :
    public Component
{
    std::shared_ptr<AnimationModel> m_Animation_Model;
    std::string m_SourcePath = "asset\\model\\M_otorii.obj";

    std::string mAnimationName1 = "asset\\model\\Akai_Idle.fbx";
    std::string mAnimationName2 = "asset\\model\\Akai_Run.fbx";

    bool m_IsVariable = false;
    int mFrame = 0;
    float mBlendRate = 0.0f;
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


    // Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override
    {
        m_Animation_Model =
            ResourceManger<AnimationModel>::GetResource(m_SourcePath.c_str());

        m_Animation_Model->LoadAnimation(mAnimationName1.c_str(), "Idle");
        m_Animation_Model->LoadAnimation(mAnimationName2.c_str(), "Run");

        mFrame = 0;
    };

    virtual void Uninit() override {};

    virtual void Update() override {
        m_Animation_Model->Update("Idle","Run",mFrame,mBlendRate);
        mFrame++;
        if (GetKeyboardPress(DIK_W)) {
            mBlendRate += 0.03f;
        }
        else
        {
            mBlendRate -= 0.03f;
        }

        if (mBlendRate >= 1.0f)
            mBlendRate = 1.0f;
        if (mBlendRate <= 0.0f)
            mBlendRate = 0.0f;
    };

    virtual void Draw() override
    {
        m_Animation_Model->Draw();

    };

    virtual void DrawImgui()  override {};

};

