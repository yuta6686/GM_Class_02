#pragma once
#include "Component.h"
#include "gameObject.h"
#include "scene.h"
#include "manager.h"
#include "player.h"

class TrackingComponent :
    public Component
{
private:
    GameObject* m_Target;

    //  Velocityコンポーネントとして実装
    D3DXVECTOR3 m_Velocity;
public:

    virtual void Init() override
    {
        std::shared_ptr<Scene> scene = Manager::GetScene();
        m_Target = scene->GetGameObject<Player>();

        //  Velocityコンポーネントとして実装
        m_Velocity = { 0.0f,0.0f,0.0f };
    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {        
        const D3DXVECTOR3 targetpos = m_Target->GetPosition();
        const D3DXVECTOR3 enemypos = m_Parent->GetPosition();        

        //  エネミーからプレイヤーへの長さ
        D3DXVECTOR3 direction = targetpos - enemypos;      

        

        //  正規化　向きを取る　(-1.0f ～ 1.0f）
        D3DXVec3Normalize(&direction, &direction);

        m_Velocity = direction * 0.1f;

        //m_Parent->SetRotation({ acosf(direction.x),asinf(direction.y),asinf(direction.z) });
        m_Parent->SetRotation({ acosf(direction.x),0.0f,0.0f });


        //  Velocityコンポーネントとして実装
        m_Parent->SetPosition(enemypos + m_Velocity);
    }

    virtual void Draw() override
    {
    }

    virtual void DrawImgui() override
    {
    }

};

