#pragma once
//  ---------------------------------------------------------
//  MatrixComponent [MatrixComponent.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/08/10
//  ------------------------summary--------------------------
//  - Matrix 2D ,3D
//  ---------------------------------------------------------

#include "component.h"
#include "scene.h"

#include "camera.h"

class MatrixComponent :
    public Component
{
private:
    bool m_Is2D = false;
    bool m_IsBillboard = false;
    bool m_IsInvertXYRotate = false;

    std::shared_ptr<Scene> m_Scene;

    Camera* m_Camera;
public:    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()  override {};

    void SetIs2D(bool flag = true) {
        m_Is2D = flag;
    }

    void SetIsBillboard(bool flag = true) { m_IsBillboard = flag; }
    void SetIsInvertXYRotate(bool flag = true) { m_IsInvertXYRotate = flag; }
};

