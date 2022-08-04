#pragma once
#include "scene.h"
#include "CO_3DPloygonTest.h"
class Transition;
class CO_3DPolygon_circle;
class TitleScene :
    public Scene
{
    std::vector<int> a;
    Transition* m_Fade;
    std::vector<CO_3DPloygonTest*> m_SwitchToScenes;
    std::vector<std::vector<CO_3DPolygon_circle*>> m_Circles;

    float m_Angle=1.0f;
public:
    // Scene ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Update()override;
};

