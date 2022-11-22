#pragma once
/** ---------------------------------------------------------
 *  [vertex_change_to_game_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/22
 * ------------------------summary--------------------------
 * @brief  
 ** ---------------------------------------------------------*/
#include "vertex_changer_color_component.h"

class VertexChangeComponent_ToGame :
    public VertexChangerComponent_Color
{
private:
    const D3DXVECTOR3 DEFAULT_SCALE = { 1.5f,3.0f,1.0f };
    const D3DXVECTOR4 FRONT_FACE_COLOR = { 0.75f,0.75f,0.75f,0.75f };
    const D3DXVECTOR4 BACK_FACE_COLOR = { 0.25f,0.25f,0.25f,1.0f };
    const D3DXVECTOR4 TO_GAME_COLOR = { 0.0f,1.0f,1.0f,1.0f };
    const D3DXVECTOR4 TO_EXIT_COLOR = { 1.0f,0.0f,0.0f,1.0f };   
    const float ANGLE_MAX = 30.0f;

    Player* m_Player;
    class Audio* m_SE;

    float m_first_degree = 0.0f;
    float m_degree = 0.0f;
    float m_degree_fixation;

    bool m_IsInSide = false;
    bool m_IsToGame = false;
    bool m_IsToExit = false;

    bool once_flag = false;

    D3DXVECTOR3 m_PlayerForwardVector;
    D3DXVECTOR3 m_myScale = DEFAULT_SCALE;

public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void DrawImgui() override;

    bool GetIsToExit()const { return m_IsToExit; }
    bool GetIsToGame()const { return m_IsToGame; }
    bool GetIsToExitAndInside()const { return m_IsToExit & m_IsInSide; }
    bool GetIsToGameAndInside()const { return m_IsToGame && m_IsInSide; }

    D3DXVECTOR4 GetFrontFaceColor()const { return FRONT_FACE_COLOR; }
    D3DXVECTOR4 GetBackFaceColor()const { return BACK_FACE_COLOR; }
    D3DXVECTOR4 GetToGameColor()const { return TO_GAME_COLOR; }
    D3DXVECTOR4 GetToExitColor()const { return TO_EXIT_COLOR; }
};

