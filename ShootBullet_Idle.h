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

    // ShootBullet ����Čp������܂���
    virtual ShootBullet* CreateNextState() override;

    // ShootBullet ����Čp������܂���
    virtual void DrawImgui() override;
};

