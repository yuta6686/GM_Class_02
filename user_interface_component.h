#pragma once
/** ---------------------------------------------------------
 *  [user_interface_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  
 * todo インライン関数整理
 ** ---------------------------------------------------------*/
#include "component.h"

#include "texture.h"

enum TEXTURE_DEPLOY {
    DEPLOY_CENTER = 0,
    DEPLOY_LEFTUP,
    DEPLOY_RIGHTUP,
    DEPLOY_LEFTDOWN,
    DEPLOY_RIGHTDOWN,
    DEPLOY_LEFT_MOVE_RIGHT,
    DEPLOY_SEPALATE_UP_DOWN,
    DEPLOY_MAX,
};
// --------main_positionの説明-----------------
// 
//  if(deploy_index!=DEPLOY_LEFT_MOVE_RIGHT)
// 
//      -->幅、高さとして働く
// 
//  if(deploy_index == DEPLOY_LEFT_MOVE_RIGHT)
// 
//      -->基準位置として働く
// 
// --------main_positionの説明-----------------

struct UI_Information {
    std::string _texture = "asset\\texture\\Rect.png";
    bool _is_change_vertex = false;

    int _deploy_index = DEPLOY_CENTER;
    D3DXVECTOR3 _main_pos = { SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f };
    D3DXVECTOR4 _color = { 1.0f,1.0f,1.0f,1.0f };
    float _right_pos = 500.0f;
    float _left_pos = 0.0f;
    
    float _up_pos = 500.0f;
    float _down_pos = 0.0f;
};
class UserInterfaceComponent :
    public Component
{
private:
    VERTEX_3D m_vertex[4];
    ID3D11Buffer* m_VertexBuffer = NULL;


    std::shared_ptr<Resource> m_Texture;
    std::string m_TextureName = "asset\\texture\\Rect.png";

    int m_DeployIndex = DEPLOY_CENTER;

    D3DXVECTOR3 m_mainPos = { 100.0f,100.0f,0.0f };
    D3DXVECTOR3 m_mainPosDouble = m_mainPos * 2.0f;
    D3DXVECTOR3 m_Offset = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };

    D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
            
    float m_RightXPosition = SCREEN_WIDTH;
    float m_LeftXPosition =  0.0f;

    float m_UpXPosition = SCREEN_WIDTH / 2.0f;
    float m_DownXPosition = SCREEN_HEIGHT / 2.0f;

    bool m_IsChangeVertex = false;

public:
    virtual void Init()override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override ;

    virtual void DrawImgui()  override;

    void SetUIInfo(UI_Information inf) {
        m_TextureName = inf._texture;
        LoadTexture(m_TextureName);
        SetIsChangeVertex(inf._is_change_vertex);
        SetDeployIndex(inf._deploy_index);

        SetWidthHeight(inf._main_pos);
        SetColor(inf._color);
        
        SetRightXPosition(inf._right_pos);
        SetLeftXPosition(inf._left_pos);

        SetUpXPosition(inf._up_pos);
        SetDownXPosition(inf._down_pos);

        Init();
    }

    void SetRightXPosition(const float& pos) { m_RightXPosition = pos; }
    void SetLeftXPosition(const float& pos) { m_LeftXPosition = pos; }
    void SetUpXPosition(const float& pos) { m_UpXPosition = pos; }
    void SetDownXPosition(const float& pos) { m_DownXPosition = pos; }


    void LoadTexture(std::string texture) {
        m_Texture = ResourceManger<Texture>::GetResource(texture);        
    }

    void SetDeployIndex(const int& index) { m_DeployIndex = index; }

    void SetWidthHeight(D3DXVECTOR3 widthheight) { m_mainPos = widthheight; }

    void SetIsChangeVertex(bool flag = true) { m_IsChangeVertex = flag; }
    
    void SetColor(const D3DXVECTOR4& color) { m_Color = color; }
    void SetAlpha(const float& alpha) { m_Color.w = alpha; }

    void InitVertex();
    void ChangeVertex(VERTEX_3D* vertex);

    void ChangeVertexDraw();
};

