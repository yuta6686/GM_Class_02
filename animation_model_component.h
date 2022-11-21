#pragma once
#include "component.h"
#include "resource_manager.h"

class AnimationModel;
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
        std::string aPath1, std::string aName1,  //  �A�j���[�V�����f�[�^1
        std::string aPath2, std::string aName2); //   �A�j���[�V�����f�[�^2
        

    void SetIsVariable(bool flag = true);

    //void SetDiffuse(D3DXCOLOR diff) { m_Animation_Model->SetDiffuse(diff); }

    AnimationModelComponent() {}
    AnimationModelComponent(std::string path) :m_SourcePath(path) {}


    // Component ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override {};

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()  override {};
};

