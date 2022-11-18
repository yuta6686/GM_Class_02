#pragma once

#include "component.h"
#include "AnimationModel.h"
#include "ResourceManager.h"

class AnimationModelComponent :
    public Component
{
    std::shared_ptr<AnimationModel> m_Animation_Model;
    std::string m_SourcePath = "asset\\model\\Akai_Idle.fbx";

    std::string mAnimationPath1 = "asset\\model\\Akai_Idle.fbx";
    std::string mAnimationPath2 = "asset\\model\\Akai_Run.fbx";

    std::string mAnimationName1 = "Idle";
    std::string mAnimationName2 = "Run";

    bool m_IsVariable = false;
    int mFrame = 0;
    float mBlendRate = 0.0f;
public:
    
    void LoadAnimationData(std::string mPath,// ���f���f�[�^
        std::string aPath1,std::string aName1,  //  �A�j���[�V�����f�[�^1
        std::string aPath2,std::string aName2) //   �A�j���[�V�����f�[�^2
    {
        //  ���f���p�X
        m_SourcePath = mPath;

        //  �A�j���[�V����1�f�[�^
        mAnimationPath1 = aPath1;
        mAnimationName1 = aName1;

        //  �A�j���[�V����2�f�[�^
        mAnimationPath2 = aPath2;
        mAnimationName2 = aName2;

        //  ���[�h
        m_Animation_Model =
            ResourceManger<AnimationModel>::GetResource(m_SourcePath.c_str());
        m_Animation_Model->LoadAnimation(mAnimationPath1.c_str(), mAnimationName1.c_str());
        m_Animation_Model->LoadAnimation(mAnimationPath2.c_str(), mAnimationName2.c_str());
    }

    void SetIsVariable(bool flag = true) {
        m_IsVariable = flag;
    }

    //void SetDiffuse(D3DXCOLOR diff) { m_Animation_Model->SetDiffuse(diff); }

    AnimationModelComponent() {}
    AnimationModelComponent(std::string path) :m_SourcePath(path) {}


    // Component ����Čp������܂���
    virtual void Init() override
    {
        m_Animation_Model =
            ResourceManger<AnimationModel>::GetResource(m_SourcePath.c_str());        
        

        mFrame = 0;
    };

    virtual void Uninit() override {};

    virtual void Update() override {
        m_Animation_Model->Update(mAnimationName1.c_str(), mAnimationName2.c_str(), mFrame, mBlendRate);
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

