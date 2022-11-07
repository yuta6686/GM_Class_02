#pragma once
#include "scene.h"
#include "MyImgui.h"
#include "ParticleObject.h"
#include "player.h"

class DebugScene :
    public Scene
{
private:
    ParticleObject* _particleObject;
    Player* _player;
    void SetParticle();
    int _particle1FrameNum = 1;
public:
    // Scene ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Update() override;
    virtual void Draw()override;

};

