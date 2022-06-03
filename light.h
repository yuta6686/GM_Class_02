#pragma once
#include "gameObject.h"
#include "renderer.h"
class Light :
    public GameObject
{
private:
    LIGHT m_Light;
public:
      
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

