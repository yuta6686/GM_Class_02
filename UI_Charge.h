#pragma once
#include "UserInterface.h"
class UI_Charge :
    public UserInterface
{
private:
    inline static const float COUNTER_MAX = 123.0f;
    inline static const float CHARGE_SPEED = 0.5f;
    inline static const float MAIN_POS_X = 100.0f;
    inline static const float MAIN_POS_Y = 15.0f;
    inline static const float ATTENUATION = 0.8f;
    float m_Counter = 1.0f;
    float m_Attenuation = ATTENUATION;
    bool m_IsDecrease;
public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    float GetChargeSpeed()const
    {
        return CHARGE_SPEED;
    }

    void AddCounter(const float& add);
    void SetCounter(const float& add);
    void SetAttenuation(const float& att);
    void SetIsDecrease(const bool& flag) { 
        m_IsDecrease = flag; 
    }
};



