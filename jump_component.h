#pragma once
//  ---------------------------------------------------------
//  JumpComponent [jump_component.h]
//                                  Author: –öàV—D‘¾
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  ƒWƒƒƒ“ƒv
//  ---------------------------------------------------------
#include "component.h"
#include "manager.h"

class VelocityComponent;
class JumpComponent :
    public Component
{
private:
    inline static const float JUMP = 0.6f;
    inline static const float GRAVITY = 0.01f;
    inline static const D3DXVECTOR3 ATTENUATION = { 0.9f,0.99f,0.9f };        

    std::shared_ptr<Scene> m_Scene;
public:    
    VelocityComponent* m_VelocityCom;

    virtual void Init() override;

    virtual void Uninit() override
    {
    }
    virtual void Update() override;

    virtual void Draw() override {}
    virtual void DrawImgui() override {}
};

