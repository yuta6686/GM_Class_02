#pragma once
#include "component_object.h"
#include "gameObject.h"
class ShootBullet :
    public ComponentObject
{
protected:
    bool m_IsNextState = false;
public:    
    virtual void Init() override=0;

    virtual void Uninit() override=0;

    virtual void Update() override=0;

    virtual void Draw() override=0;

    virtual bool GetIsNextState() { return m_IsNextState; }
    virtual ShootBullet* CreateNextState() = 0;
};

