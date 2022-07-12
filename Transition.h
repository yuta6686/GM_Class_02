#pragma once
#include "UserInterface.h"
class Transition :
    public UserInterface
{
private:
    int m_Count=0;

    void FadeIn();
    void FadeOut();

    bool m_IsFadeIn;
    bool m_IsFadeOut;

    bool m_IsFinishFadeIn = false;
    bool m_IsTransition = false;

    static const int FADE_TIME = 60;
public:  

    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    void SetFadeIn()
    {
        m_IsFadeIn = true;
        m_IsFadeOut = false;
        m_Count = FADE_TIME;
    }

    void SetFadeOut()
    {
        m_IsFadeOut = true;
        m_IsFadeIn = false;

        m_Count = 0;
    }

    bool GetIsTransition()const {
        return m_IsTransition;
    }

    bool GetIsFinishFadeIn()const {
        return m_IsFinishFadeIn;
    }
};

