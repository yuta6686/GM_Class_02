#include "animation_model_component.h"
#include "animation_model.h"

void AnimationModelComponent::LoadAnimationData(std::string mPath,// モデルデータ
    std::string aPath1, std::string aName1,  //  アニメーションデータ1
    std::string aPath2, std::string aName2) //   アニメーションデータ2
{
    //  モデルパス
    m_SourcePath = mPath;

    //  アニメーション1データ
    mAnimationPath1 = aPath1;
    mAnimationName1 = aName1;

    //  アニメーション2データ
    mAnimationPath2 = aPath2;
    mAnimationName2 = aName2;

    //  ロード
    m_Animation_Model =
        ResourceManger<AnimationModel>::GetResource(m_SourcePath.c_str());
    m_Animation_Model->LoadAnimation(mAnimationPath1.c_str(), mAnimationName1.c_str());
    m_Animation_Model->LoadAnimation(mAnimationPath2.c_str(), mAnimationName2.c_str());
}

void AnimationModelComponent::Init()
{
    m_Animation_Model =
        ResourceManger<AnimationModel>::GetResource(m_SourcePath.c_str());


    mFrame = 0;
};

void AnimationModelComponent::Update()
{
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
}

void AnimationModelComponent::Draw()
{
    m_Animation_Model->Draw();
};

void AnimationModelComponent::SetIsVariable(bool flag) {
    m_IsVariable = flag;
}
