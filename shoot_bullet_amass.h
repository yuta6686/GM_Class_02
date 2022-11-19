#pragma once
#include "shoot_bullet.h"
class UI_Charge;
class Scene;
class ShootBullet_Amass :
    public ShootBullet
{
private:
    int m_BulletNum = 0;
    int m_Counter = 0;
    class UI_Charge* m_uiCharge;
    std::shared_ptr<Scene> m_Scene;
public:

    // ShootBullet ����Čp������܂���
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;    
    virtual ShootBullet* CreateNextState() override;
};
