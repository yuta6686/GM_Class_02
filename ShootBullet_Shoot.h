#pragma once
#include "ShootBullet.h"
class Bullet;
class Player;
class Scene;
class UI_Charge;
class ShootBullet_Shoot :
    public ShootBullet
{
private:
    int m_BulletNum = 0;
    int m_Counter = 0;
    int m_AmassCounter = 0;
    int m_FirstBulletNum = 0;
    class Bullet* m_Bullet=nullptr;
    class Player* m_Player=nullptr;
    std::shared_ptr<Scene> m_Scene = nullptr;    
public:
    ShootBullet_Shoot() {}
    ShootBullet_Shoot(const int& bulletNum,const int& counter) { 
        m_BulletNum = m_FirstBulletNum = bulletNum; 
        m_AmassCounter = counter;
    }
    // ShootBullet ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;    
    virtual ShootBullet* CreateNextState() override;
};

