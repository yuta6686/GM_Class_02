#pragma once
#include "main.h"
#include "Component.h"
class BulletComponent :
    public Component
{
private:

    D3DXVECTOR3 m_Velocity;	//	‘¬“x
public:       
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;


    void SetVelocity(D3DXVECTOR3 vel) {
        m_Velocity = vel;
    }

    void AddParentPos(D3DXVECTOR3 addvalue); 
};

