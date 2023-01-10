#include "stdafx.h"
#include "vertex_change_to_game_component.h"
#include "audio.h"
#include "player.h"


 void VertexChangeComponent_ToGame::Init()
{
    std::shared_ptr<Scene> scene = Manager::GetScene();
    _player = scene->GetGameObject<Player>();
    _playerForwardVector = _player->GetForward();

    _se = scene->AddGameObject<Audio>(LAYER_AUDIO);
    _se->Load("asset\\audio\\SE_Scroll.wav");

    //  中心から30度の視野角内に写っているかわかる
    D3DXVECTOR3 playerForwardvec = _player->GetForward();
    D3DXVec3Normalize(&playerForwardvec, &playerForwardvec);


    D3DXVECTOR3 myForwardvec = m_Parent->GetPosition() - _player->GetPosition();
    D3DXVec3Normalize(&myForwardvec, &myForwardvec);

    _first_degree = MyMath::GetDegree(acosf(D3DXVec3Dot(&playerForwardvec, &myForwardvec)));

    if (_first_degree <= ANGLE_MAX) {
        _isToGame = true;
        m_Color = TO_EXIT_COLOR;
    }
    else if (_first_degree >= 150.0f) {
        _isToExit = true;
        m_Color = TO_EXIT_COLOR;
    }
    else
    {
        _isToGame = false;
        _isToExit = false;
        m_Color = BACK_FACE_COLOR;
    }
}


 void VertexChangeComponent_ToGame::Update()
{
    //  中心から30度の視野角内に写っているかわかる
    D3DXVECTOR3 playerForwardvec = _player->GetForward();
    D3DXVec3Normalize(&playerForwardvec, &playerForwardvec);


    D3DXVECTOR3 myForwardvec = m_Parent->GetPosition() - _player->GetPosition();
    D3DXVec3Normalize(&myForwardvec, &myForwardvec);

    _degree = MyMath::GetDegree(acosf(D3DXVec3Dot(&playerForwardvec, &myForwardvec)));



    if (_degree <= ANGLE_MAX)
    {
        float lerp_scale = (1.0f - _degree / ANGLE_MAX) * 3.0f;

        _myScale.x = DEFAULT_SCALE.x + lerp_scale;
        _myScale.y = DEFAULT_SCALE.y + lerp_scale;
        _myScale.z = DEFAULT_SCALE.z + lerp_scale;

        m_Parent->SetScale(_myScale);
        _isInSide = true;


        if (_degree / ANGLE_MAX >= 0.9f) {
            if (_onceFlag == false) {
                _onceFlag = true;
                _se->Play();
            }
        }
        else {
            _onceFlag = false;
        }
    }
    else
    {
        m_Parent->SetScale(DEFAULT_SCALE);
        _isInSide = false;
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

    if (_isInSide) {
        m_Color += FRONT_FACE_COLOR;
    }
}



 void VertexChangeComponent_ToGame::DrawImgui()
{
    ImGui::Text("angle:%.2f", _degree);
    ImGui::Text("m_first_degree:%.2f", _first_degree);
    ImGui::Checkbox("IsToGame", &_isToGame);
    ImGui::Checkbox("IsToExit", &_isToExit);
    ImGui::Checkbox("IsInside", &_isInSide);
}