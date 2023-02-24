#pragma once
/** ---------------------------------------------------------
 *  JumpComponent [animation_model_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  アニメーションモデル（Assimp）
 * 
 ** ---------------------------------------------------------*/
#include "component.h"


class AnimationModel;
class AnimationModelComponent :
    public Component
{
    std::shared_ptr<AnimationModel> m_Animation_Model;
    std::string m_SourcePath = "asset\\model\\Akai_Idle.fbx";

    std::string _animationPath1 = "asset\\model\\Akai_Idle.fbx";
    std::string _animationPath2 = "asset\\model\\Akai_Run.fbx";

    std::string _animationName1 = "Idle";
    std::string _animationName2 = "Run";

    bool _isVariable = false;
    int _frame = 0;
    float mBlendRate = 0.0f;
public:
    
    void LoadAnimationData(std::string mPath,// モデルデータ
        std::string aPath1, std::string aName1,  //  アニメーションデータ1
        std::string aPath2, std::string aName2); //   アニメーションデータ2
        

    void SetIsVariable(bool flag = true);

    //void SetDiffuse(D3DXCOLOR diff) { m_Animation_Model->SetDiffuse(diff); }

    AnimationModelComponent() {}
    AnimationModelComponent(std::string path) :m_SourcePath(path) {}


    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()  override {};
};

