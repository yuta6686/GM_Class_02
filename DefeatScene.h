#pragma once
#include "scene.h"

class Transition;
class CO_Select;
class DefeatScene :
    public Scene
{
private:
    Transition* m_Fade;   
    CO_Select* m_Select;

    bool m_NextIsExit = false;
    bool m_NextIsGame = false;
    bool m_NextIsTitle = false;
    bool m_ChangeScene = false;
public:
    // Scene ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Update()override;
};

