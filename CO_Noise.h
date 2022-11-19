#pragma once
#include "renderer.h"
#include "component_object.h"
#include "user_interface_component.h"
#include "vertex_change_component.h"

class CO_Noise :
    public ComponentObject
{
private:
    
public:
    virtual void Init()override {
        m_TypeName = "CO_UI_test";        
            
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_TEST);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        ModelDrawComponent* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
            mdc->SetSourcePath("asset\\model\\curtains.obj");
           


        //UI_Information uiinf;
        //uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
        //uiinf._texture = "asset\\texture\\grad_sino.png";

        //D3DXVECTOR3 widthheight = { 1500.0f,1080.0f ,0.0f };
        //uiinf._main_pos = widthheight / 6.0f;

        //uiinf._is_change_vertex = true;
        //uiinf._up_pos = -10.0f;
        //uiinf._down_pos = 10.0f;

        //uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

        //m_UIComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
        //m_UIComponent->SetUIInfo(uiinf);



        AddComponent<ImGuiComponent>(COMLAYER_SECOND);



        ComponentObject::Init();

        m_Position.y = 0.0f;
        float scale = 10.0f;
        m_Scale = { scale,scale * 2.0f,scale };
    }

    virtual void Uninit()override
    {
        ComponentObject::Uninit();

        Renderer::SetValiable({ 0.0f,1.0f,1.0f,1.0f });

    }

    virtual void Update()override
    {
        ComponentObject::Update();                        
    }

    virtual void Draw()override
    {
        if (Renderer::m_Valiable.pad2 >= 100.0f) {
            Renderer::m_Valiable.pad1 = 0.0f;
            Renderer::m_Valiable.pad2 = 0.0f;
        }

        Renderer::m_Valiable.pad1 += 0.0f;
        Renderer::m_Valiable.pad2 += 0.05f;

        Renderer::SetValiable(Renderer::m_Valiable);

        ComponentObject::Draw();
    }
};

