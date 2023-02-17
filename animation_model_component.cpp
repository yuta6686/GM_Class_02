#include "animation_model_component.h"
#include "animation_model.h"

void AnimationModelComponent::LoadAnimationData(std::string mPath,// ���f���f�[�^
    std::string aPath1, std::string aName1,  //  �A�j���[�V�����f�[�^1
    std::string aPath2, std::string aName2) //   �A�j���[�V�����f�[�^2
{
    //  ���f���p�X
    m_SourcePath = mPath;

    //  �A�j���[�V����1�f�[�^
    _animationPath1 = aPath1;
    _animationName1 = aName1;

    //  �A�j���[�V����2�f�[�^
    _animationPath2 = aPath2;
    _animationName2 = aName2;

    //  ���[�h
    m_Animation_Model =
        ResourceManager<AnimationModel>::GetResource(m_SourcePath.c_str());
    m_Animation_Model->LoadAnimation(_animationPath1.c_str(), _animationName1.c_str());
    m_Animation_Model->LoadAnimation(_animationPath2.c_str(), _animationName2.c_str());
}

void AnimationModelComponent::Init()
{
    m_Animation_Model =
        ResourceManager<AnimationModel>::GetResource(m_SourcePath.c_str());


    _frame = 0;
}
void AnimationModelComponent::Uninit()
{    
}


void AnimationModelComponent::Update()
{
    m_Animation_Model->Update(_animationName1.c_str(), _animationName2.c_str(), _frame, mBlendRate);
    _frame++;
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
    _isVariable = flag;
}
