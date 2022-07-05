#pragma once
#include "ShootBullet.h"
class UI_Charge;
class ShootBullet_Amass :
    public ShootBullet
{
private:
    int m_BulletNum = 0;
    int m_Counter = 0;
    class UI_Charge* m_uiCharge;
public:

    // ShootBullet ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;    
    virtual ShootBullet* CreateNextState() override;
};

