#pragma once
/** ---------------------------------------------------------
 *  BulletComponent [bullet_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  
 ** ---------------------------------------------------------*/
#include "component.h"
#include "particle_object.h"
class BulletComponent :
    public Component
{
private:

    D3DXVECTOR3 m_Velocity;	//	‘¬“x
    inline static const float VELOCITY_MIN = 0.001f;

    inline static const float GRABITY = -0.01f;
    ParticleObject* m_Particle;
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

