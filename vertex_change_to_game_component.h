#pragma once
/** ---------------------------------------------------------
 *  [vertex_change_to_game_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/08/04
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

    class Player* _player;
    class Audio* _se;

    float _first_degree = 0.0f;
    float _degree = 0.0f;
    float _degree_fixation;

    bool _isInSide = false;
    bool _isToGame = false;
    bool _isToExit = false;

    bool _onceFlag = false;

    D3DXVECTOR3 _playerForwardVector;
    D3DXVECTOR3 _myScale = DEFAULT_SCALE;

public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void DrawImgui() override;

    bool GetIsToExit()const { return _isToExit; }
    bool GetIsToGame()const { return _isToGame; }
    bool GetIsToExitAndInside()const { return _isToExit & _isInSide; }
    bool GetIsToGameAndInside()const { return _isToGame && _isInSide; }

    D3DXVECTOR4 GetFrontFaceColor()const { return FRONT_FACE_COLOR; }
    D3DXVECTOR4 GetBackFaceColor()const { return BACK_FACE_COLOR; }
    D3DXVECTOR4 GetToGameColor()const { return TO_GAME_COLOR; }
    D3DXVECTOR4 GetToExitColor()const { return TO_EXIT_COLOR; }
};

