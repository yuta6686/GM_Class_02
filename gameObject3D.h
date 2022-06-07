#pragma once
#include "gameObject.h"
#include "model.h"
#include <memory>
class GameObject3D :
    public GameObject
{
public:
    
    virtual void Init() override=0;
    virtual void Uninit() override=0;
    virtual void Update() override=0;
    virtual void Draw() override=0;

    
};

