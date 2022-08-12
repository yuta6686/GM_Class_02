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

    // ShootBullet ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual ShootBullet* CreateNextState() override;

    // ShootBullet ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void DrawImgui() override;
};

