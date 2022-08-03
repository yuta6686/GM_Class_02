#pragma once
#include "Component.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"

class MatrixComponent :
    public Component
{
private:
    bool m_Is2D = false;
    bool m_IsBillboard = false;
    std::shared_ptr<Scene> m_Scene;
    Camera* m_Camera;
public:


    // Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()  override {};

    void SetIs2D(bool flag = true) {
        m_Is2D = flag;
    }

    void SetIsBillboard(bool flag = true) { m_IsBillboard = flag; }
};

