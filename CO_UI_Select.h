#pragma once
#include "component_object.h"
#include "user_interface_component.h"
#include "hp_component.h"
#include "vertex_change_component.h"
#include "blink_scale_component.h"

class CO_UI_Select :
    public ComponentObject
{
private:
//  inline static const ïœêî
    inline static const std::string m_FileName_Select_True = "asset\\texture\\UI_Select_true.png";
    inline static const std::string m_FileName_Select_True_Blue = "asset\\texture\\UI_Select_true_blue.png";
    inline static const std::string m_FileName_Select_False = "asset\\texture\\UI_Select_false.png";
    inline static const std::string m_FileName_Select_False_Blue = "asset\\texture\\UI_Select_false_blue.png";
    inline static const std::vector<std::string> m_FileNameBox
        = { 
        "asset\\texture\\UI_GiveUp.png" ,
        "asset\\texture\\UI_Continue.png" ,
        "asset\\texture\\UI_ReturnToTitle.png" 
    };
    

//  í èÌÉÅÉìÉoïœêî
    bool m_IsString = false;
    D3DXVECTOR3 m_TruePosition;
    D3DXVECTOR3 m_FalsePosition;
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        {
            auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);

            for (auto x : m_FileNameBox) {
                uifc->LoadTexture(x);
            }

            uifc->LoadTexture(m_FileName_Select_True);
            uifc->LoadTexture(m_FileName_Select_False);
            

            uifc->SetDeployIndex(DEPLOY_CENTER);
            uifc->SetWidthHeight({ 275.0f,30.0f ,0.0f });
            uifc->SetIsChangeVertex();
            //uifc->SetLeftXPosition(HPComponent::GetLEFTPOSITION() - 25.0f);
            //uifc->SetRightXPosition(HPComponent::GetRIGHTPOSITION() + 25.0f);

        }



        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        AddComponent<BlinkComponent_Scale>(COMLAYER_SECOND)
            ->SetParameter(AXIS_XY, 0.0f, 1.0f, 1.0f);

        ComponentObject::Init();
    }

    static std::string GetFileName_SelectTrue() { return m_FileName_Select_True; }
    static std::string GetFileName_SelectTrue_Blue() { return m_FileName_Select_True_Blue; }
    static std::string GetFileName_SelectFalse() { return m_FileName_Select_False; }
    static std::string GetFileName_SelectFalse_Blue() { return m_FileName_Select_False_Blue; }
    static std::vector<std::string> GetFileName_Box() { return m_FileNameBox; }

    void SetIsString(bool flag = true) { m_IsString = flag; }
    bool GetIsString()const { return m_IsString; }

    void SetTrue_False_Position(
        const D3DXVECTOR3& true_pos,const float& up)
    {
        m_TruePosition = true_pos;
        m_FalsePosition = true_pos;
        m_FalsePosition.y -= up;
    }

    D3DXVECTOR3 GetTrue_False_Position(bool flag) {
        if (flag) 
            return m_TruePosition;

        return m_FalsePosition;
    }

    void PositionAdaptation(bool flag)
    {
        if(flag)
            m_Position = m_TruePosition;
        else
            m_Position = m_FalsePosition;
    }
};

