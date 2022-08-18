#pragma once
#include "Component.h"
#include "ShootBullet_Idle.h"
class ShootBulletComponent :
    public Component
{
private:
    class ShootBullet* m_ShootBullet;

    bool m_IsUseBullet = true;
public:    
    ShootBullet* GetShootBullet() { return m_ShootBullet; }
    void SetIsUseBullet(bool flag = true) { m_IsUseBullet = flag; }
    virtual void Init() override
    {
        m_ShootBullet = new ShootBullet_Idle();
        m_ShootBullet->Init();
    }

    virtual void Uninit() override
    {
        m_ShootBullet->Uninit();
        delete m_ShootBullet;
    }

    virtual void Update() override
    {
        if (!m_IsUseBullet)return;

        m_ShootBullet->Update();

        if (m_ShootBullet->GetIsNextState()) {
            //	����state�̃|�C���^�������炤�B
            ShootBullet* sb = m_ShootBullet->CreateNextState();

            //	���̃|�C���^�͏����B
            m_ShootBullet->Uninit();
            delete m_ShootBullet;

            //	�V�����|�C���^�����
            m_ShootBullet = sb;
            m_ShootBullet->Init();
        }
    }

    virtual void Draw() override
    {
    }

    virtual void DrawImgui() override
    {        
        ImGui::Checkbox("IsUseBullet", &m_IsUseBullet);
    }
};

