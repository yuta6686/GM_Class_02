#pragma once
#include "VertexChangerComponent_Color.h"
class VertexChangeComponent_ToGame :
    public VertexChangerComponent_Color
{
private:
    Player* m_Player;
    const D3DXVECTOR4 m_FrontFaceColor = { 0.75f,0.75f,0.75f,0.75f };
    const D3DXVECTOR4 m_BackFaceColor = { 0.25f,0.25f,0.25f,1.0f };
    const D3DXVECTOR4 m_ToGameColor = { 0.0f,1.0f,1.0f,1.0f };
    const D3DXVECTOR4 m_ToExitColor = { 1.0f,0.0f,0.0f,1.0f };   



    const float m_AngleMax = 30.0f;
    D3DXVECTOR3 m_PlayerForwardVector;
    float m_first_degree = 0.0f;
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

        //  中心から30度の視野角内に写っているかわかる
        D3DXVECTOR3 playerForwardvec = m_Player->GetForward();
        D3DXVec3Normalize(&playerForwardvec, &playerForwardvec);


        D3DXVECTOR3 myForwardvec = m_Parent->GetPosition() - m_Player->GetPosition();
        D3DXVec3Normalize(&myForwardvec, &myForwardvec);

        m_first_degree = MyMath::GetDegree(acosf(D3DXVec3Dot(&playerForwardvec, &myForwardvec)));

        if (m_first_degree <= m_AngleMax) {
            m_IsToGame = true;
            m_Color = m_ToGameColor;
        }
        else if (m_first_degree >= 150.0f) {
            m_IsToExit = true;
            m_Color = m_ToExitColor;
        }
        else
        {
            m_IsToGame = false;
            m_IsToExit = false;
            m_Color = m_BackFaceColor;
        }
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
            float lerp_scale = (1.0f - m_degree / m_AngleMax) * 3.0f;

            m_myScale.x = DEFAULT_SCALE.x + lerp_scale;
            m_myScale.y = DEFAULT_SCALE.y + lerp_scale;
            m_myScale.z = DEFAULT_SCALE.z + lerp_scale;

            m_Parent->SetScale(m_myScale);
            m_IsInSide = true;
        }        
        else
        {            
            m_Parent->SetScale(DEFAULT_SCALE);
            m_IsInSide = false;            
        }

        //  強制で色を変更する
        //  ゲームシーンへ ---> 青？
        //  ゲーム終了     ---> 赤？
 
        

        if (GetIsToExitAndInside()) {
            m_Color = m_ToExitColor;
            return;
        }
        else if (GetIsToGameAndInside()) {
            m_Color = m_ToGameColor;
        }
        else
        {
            m_Color = m_BackFaceColor;
        }

        if (m_IsInSide) {
            m_Color += m_FrontFaceColor;
        } 
    }



    virtual void DrawImgui() override
    {
        ImGui::Text("angle:%.2f", m_degree);
        ImGui::Text("m_first_degree:%.2f", m_first_degree);
        ImGui::Checkbox("IsToGame", &m_IsToGame);
        ImGui::Checkbox("IsToExit", &m_IsToExit);
        ImGui::Checkbox("IsInside", &m_IsInSide);
    }

    bool GetIsToExit()const
    {
        return m_IsToExit;
    }
    bool GetIsToGame()const
    {
        return m_IsToGame;
    }

    bool GetIsToExitAndInside()const {
        return m_IsToExit & m_IsInSide;
    }

    bool GetIsToGameAndInside()const
    {
        return m_IsToGame && m_IsInSide;
    }

    D3DXVECTOR4 GetFrontFaceColor()const { return m_FrontFaceColor; }
    D3DXVECTOR4 GetBackFaceColor()const { return m_BackFaceColor; }
    D3DXVECTOR4 GetToGameColor()const { return m_ToGameColor; }
    D3DXVECTOR4 GetToExitColor()const { return m_ToExitColor; }
};

