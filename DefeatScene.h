#pragma once
#include "scene.h"

class Transition;
class CO_Select;
class ParticleObject_2D;
class Audio;
class DefeatScene :
    public Scene
{
private:
    Transition* m_Fade;   
    CO_Select* m_Select;
    ParticleObject_2D* m_Particle;
    Audio* m_BGM;

    bool m_NextIsExit = false;
    bool m_NextIsGame = false;
    bool m_NextIsTitle = false;
    bool m_ChangeScene = false;
public:
    // Scene を介して継承されました
    virtual void Init() override;
    virtual void Update()override;
};

