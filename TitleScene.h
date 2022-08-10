#pragma once
#include "scene.h"
#include "CO_3DPloygonTest.h"
#include "CO_Confirmation.h"
class Audio;
class Transition;
class CO_3DPolygon_circle;
class TitleScene :
    public Scene
{
    std::vector<int> a;
    Transition* m_Fade;
    std::vector<CO_3DPloygonTest*> m_SwitchToScenes;
    std::vector<std::vector<CO_3DPolygon_circle*>> m_Circles;
    CO_Confirmation* m_Confirmation;

    float m_Angle=1.0f;
    class Audio* m_BGM;
public:
    // Scene ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Update()override;
};

