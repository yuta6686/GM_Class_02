#pragma once
/** ---------------------------------------------------------
 *  ShootBulletComponent [shoot_bullet_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  
 ** ---------------------------------------------------------*/
#include "component.h"

class ShootBulletComponent :
    public Component
{
private:
    class ShootBullet* m_ShootBullet;

    bool m_IsUseBullet = true;
public:       
    ShootBullet* GetShootBullet() { return m_ShootBullet; }
    void SetIsUseBullet(bool flag = true) { m_IsUseBullet = flag; }

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;
};

