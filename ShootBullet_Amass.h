#pragma once
#include "ShootBullet.h"
class ShootBullet_Amass :
    public ShootBullet
{
private:
    int m_BulletNum = 0;
    int m_Counter = 0;
public:

    // ShootBullet ����Čp������܂���
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;    
    virtual ShootBullet* CreateNextState() override;
};

