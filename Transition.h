#pragma once
#include "GameObject.h"
class Transition :
    public GameObject
{
private:
    ID3D11Buffer* m_VertexBuffer = NULL;
    std::shared_ptr<Resource> m_Texture;

    std::shared_ptr<VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;

    D3DXVECTOR3 m_mainPos;
    D3DXVECTOR3 m_Offset = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };
    VERTEX_3D m_vertex[4];

    int m_Count = 0;
    bool m_In = false;
    bool m_Finish = false;

    static const int FADE_TIME = 60;
public:

    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    void Start(bool in);
    bool GetFinish() { return m_Finish; }
};

