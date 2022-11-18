#pragma once
#include "component.h"
#include "my_math.h"
class Rotate2D :
    public Component
{
private:    
    float m_Angle = 1.0f;

    D3DXVECTOR3 m_CenterPosition = 
    { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f ,0.0f};


public:    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

    void SetAngleAndCenterPosition(
        const float& angle, D3DXVECTOR3 center) {
        m_Angle = angle;
        m_CenterPosition = center;
    }
};

