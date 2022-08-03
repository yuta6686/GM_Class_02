#pragma once
#include "Component.h"
#include "gameObject.h"
#include "Polygon3DComponent.h"
#include "scene.h"
#include "manager.h"
#include "player.h"

class VertexChangerComponent_Color :
    public Component
{
private:
    Player* m_Player;
    const D3DXVECTOR4 m_FrontFaceColor = { 0.75f,0.75f,0.75f,0.75f };
    const D3DXVECTOR4 m_BackFaceColor = { 0.25f,0.25f,0.25f,0.25f };
    const D3DXVECTOR4 m_ToGameColor = { 0.0f,1.0f,1.0f,1.0f };
    const D3DXVECTOR4 m_ToExitColor = { 1.0f,0.0f,0.0f,1.0f };
    
    D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };

    const float m_AngleMax = 30.0f;
    D3DXVECTOR3 m_PlayerForwardVector;
    float m_degree = 0.0f;
    float m_degree_fixation;

    bool m_IsInSide = false;
    bool m_IsToGame = false;
    bool m_IsToExit = false;

    const D3DXVECTOR3 DEFAULT_SCALE = { 1.5f,3.0f,1.0f };
    D3DXVECTOR3 m_myScale = DEFAULT_SCALE;
public:    
    virtual void Init() override
    {
        std::shared_ptr<Scene> scene = Manager::GetScene();
        m_Player = scene->GetGameObject<Player>();
        m_PlayerForwardVector = m_Player->GetForward();
    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {
        //  中心から30度の視野角内に写っているかわかる
        D3DXVECTOR3 playerForwardvec = m_Player->GetForward();
        D3DXVec3Normalize(&playerForwardvec, &playerForwardvec);


        D3DXVECTOR3 myForwardvec = m_Parent->GetPosition() - m_Player->GetPosition();
        D3DXVec3Normalize(&myForwardvec, &myForwardvec);
        
        m_degree = MyMath::GetDegree(acosf(D3DXVec3Dot(&playerForwardvec, &myForwardvec)));


        if (m_degree <= m_AngleMax)
        {
            m_Color = m_FrontFaceColor;
            float lerp_scale = (1.0f - m_degree / m_AngleMax) * 3.0f;

            m_myScale.x = DEFAULT_SCALE.x + lerp_scale;
            m_myScale.y = DEFAULT_SCALE.y + lerp_scale;
            m_myScale.z = DEFAULT_SCALE.z + lerp_scale;

            m_Parent->SetScale(m_myScale);
            m_IsInSide = true;
        }
        else
        {
            m_Color = m_BackFaceColor;
            m_Parent->SetScale(DEFAULT_SCALE);
            m_IsInSide = false;
        }

        //  強制で色を変更する
        //  ゲームシーンへ ---> 青？
        //  ゲーム終了     ---> 赤？

        //  プレイヤーが最初に向いていた方向
        D3DXVec3Normalize(&m_PlayerForwardVector, &m_PlayerForwardVector);
        m_degree_fixation = MyMath::GetDegree(acosf(D3DXVec3Dot(&m_PlayerForwardVector, &myForwardvec)));
        if (m_degree_fixation < 30.0f) {
            m_Color += m_ToGameColor;
            m_IsToGame = true;
        }
        else {
            m_IsToGame = false;
        }

        if (m_degree_fixation > 150.0f) {
            m_Color += m_ToExitColor;
            m_IsToExit = true;
        }
        else
        {
            m_IsToExit = false;
        }

    }

    virtual void Draw() override
    {
        m_Parent->GetComponent<Polygon3DComponent>()->ChangeVertexDraw(m_Color);
    }

    virtual void DrawImgui() override
    {
        ImGui::Text("angle:%.2f", m_degree);
    }

    bool GetIsToExit()const  {
        return m_IsToExit && m_IsInSide;
    }

    bool GetIsToGame()const
    {
        return m_IsToGame && m_IsInSide;
    }
};

