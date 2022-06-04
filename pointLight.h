#pragma once
#include "gameObject.h"
#include "renderer.h"
class PointLight :
    public GameObject
{
private:
    //POINT_LIGHT m_ptLight;
public:
    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};