#include "vertex_change_to_game_component.h"
#include "audio.h"

 void VertexChangeComponent_ToGame::Init()
{
    std::shared_ptr<Scene> scene = Manager::GetScene();
    m_Player = scene->GetGameObject<Player>();
    m_PlayerForwardVector = m_Player->GetForward();

    m_SE = scene->AddGameObject<Audio>(LAYER_AUDIO);
    m_SE->Load("asset\\audio\\SE_Scroll.wav");

    //  中心から30度の視野角内に写っているかわかる
    D3DXVECTOR3 playerForwardvec = m_Player->GetForward();
    D3DXVec3Normalize(&playerForwardvec, &playerForwardvec);


    D3DXVECTOR3 myForwardvec = m_Parent->GetPosition() - m_Player->GetPosition();
    D3DXVec3Normalize(&myForwardvec, &myForwardvec);

    m_first_degree = MyMath::GetDegree(acosf(D3DXVec3Dot(&playerForwardvec, &myForwardvec)));

    if (m_first_degree <= ANGLE_MAX) {
        m_IsToGame = true;
        m_Color = TO_EXIT_COLOR;
    }
    else if (m_first_degree >= 150.0f) {
        m_IsToExit = true;
        m_Color = TO_EXIT_COLOR;
    }
    else
    {
        m_IsToGame = false;
        m_IsToExit = false;
        m_Color = BACK_FACE_COLOR;
    }
}


 void VertexChangeComponent_ToGame::Update()
{
    //  中心から30度の視野角内に写っているかわかる
    D3DXVECTOR3 playerForwardvec = m_Player->GetForward();
    D3DXVec3Normalize(&playerForwardvec, &playerForwardvec);


    D3DXVECTOR3 myForwardvec = m_Parent->GetPosition() - m_Player->GetPosition();
    D3DXVec3Normalize(&myForwardvec, &myForwardvec);

    m_degree = MyMath::GetDegree(acosf(D3DXVec3Dot(&playerForwardvec, &myForwardvec)));



    if (m_degree <= ANGLE_MAX)
    {
        float lerp_scale = (1.0f - m_degree / ANGLE_MAX) * 3.0f;

        m_myScale.x = DEFAULT_SCALE.x + lerp_scale;
        m_myScale.y = DEFAULT_SCALE.y + lerp_scale;
        m_myScale.z = DEFAULT_SCALE.z + lerp_scale;

        m_Parent->SetScale(m_myScale);
        m_IsInSide = true;


        if (m_degree / ANGLE_MAX >= 0.9f) {
            if (once_flag == false) {
                once_flag = true;
                m_SE->Play();
            }
        }
        else {
            once_flag = false;
        }
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
        m_Color = TO_EXIT_COLOR;
        return;
    }
    else if (GetIsToGameAndInside()) {
        m_Color = TO_GAME_COLOR;
    }
    else
    {
        m_Color = BACK_FACE_COLOR;
    }

    if (m_IsInSide) {
        m_Color += FRONT_FACE_COLOR;
    }
}



 void VertexChangeComponent_ToGame::DrawImgui()
{
    ImGui::Text("angle:%.2f", m_degree);
    ImGui::Text("m_first_degree:%.2f", m_first_degree);
    ImGui::Checkbox("IsToGame", &m_IsToGame);
    ImGui::Checkbox("IsToExit", &m_IsToExit);
    ImGui::Checkbox("IsInside", &m_IsInSide);
}