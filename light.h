#pragma once

#include "renderer.h"
class Light :
    public ComponentObject
{
private:
    LIGHT m_Light;

    int m_index;

    inline static const float POINT_LIGHT_SPEED = 1.0f;
public:
    
      
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

   
    void InitDirectionLight(LIGHT& light);
    void InitPointLight(LIGHT& light);
    void InitAmbientLight(LIGHT& light);
};



