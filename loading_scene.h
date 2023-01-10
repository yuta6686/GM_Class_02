#pragma once
#include "scene.h"
class Loading :
    public Scene
{
private:
    class ParticleObject_2D* _particle;
    
public:    
    virtual void Init() override;
    virtual void UnInit() override;
    virtual void Update() override;

    
};

