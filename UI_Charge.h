#pragma once
#include "UserInterface.h"
class UI_Charge :
    public UserInterface
{
private:
    inline static const float COUNTER_MAX = 123.0f;
    inline static const float CHARGE_SPEED = 0.5f;
    inline static const float MAIN_POS_X = 100.0f;
    inline static const float MAIN_POS_Y = 20.0f;
    float m_Counter = 1.0f;
public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    
};


