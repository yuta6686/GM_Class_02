#pragma once
#include "ShootBullet.h"
class ShootBullet_Idle :
    public ShootBullet
{
public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;        

    // ShootBullet を介して継承されました
    virtual ShootBullet* CreateNextState() override;

    // ShootBullet を介して継承されました
    virtual void DrawImgui() override;
};

