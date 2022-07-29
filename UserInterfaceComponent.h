#pragma once
#include "Component.h"
#include "ResourceManager.h"
#include "texture.h"

enum TEXTURE_DEPLOY {
    DEPLOY_CENTER = 0,
    DEPLOY_LEFTUP,
    DEPLOY_RIGHTUP,
    DEPLOY_LEFTDOWN,
    DEPLOY_RIGHTDOWN,
    DEPLOY_MAX,
};
class UserInterfaceComponent :
    public Component
{
private:
    ID3D11Buffer* m_VertexBuffer = NULL;
    std::shared_ptr<Resource> m_Texture;

    D3DXVECTOR3 m_mainPos = { 100.0f,100.0f,0.0f };
    D3DXVECTOR3 m_mainPosDouble = m_mainPos * 2.0f;
    float m_Radius = 100.0f;
    VERTEX_3D m_vertex[4];
    D3DXVECTOR3 m_Offset = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };
    int m_DeployIndex = DEPLOY_CENTER;
    D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };
    bool m_IsChangeVertex = false;
public:
    virtual void Init()override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override ;

    virtual void DrawImgui()  override;

    void LoadTexture(std::string texture) {
        m_Texture = ResourceManger<Texture>::GetResource(texture);        
    }

    void SetDeployIndex(const int& index) { m_DeployIndex = index; }

    void SetWidthHeight(D3DXVECTOR3 widthheight) { m_mainPos = widthheight; }

    void SetIsChangeVertex(bool flag = true) { m_IsChangeVertex = flag; }
    
    void SetColor(const D3DXVECTOR4& color) { m_Color = color; }

    void InitVertex();
    void ChangeVertex(VERTEX_3D* vertex);

    void ChangeVertexDraw();
};

