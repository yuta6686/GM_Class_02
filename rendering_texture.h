#pragma once
#include "gameObject.h"
#include "component_object.h"
class RenderingTexture :
    public ComponentObject
{
private:
    VERTEX_3D m_vertex[4];
    ID3D11Buffer* m_VertexBuffer = NULL;

    inline static const D3DXVECTOR3 _screenHalf =
    { SCREEN_WIDTH ,SCREEN_HEIGHT,0.0f };

    D3DXVECTOR3 m_mainPos = _screenHalf;
    inline static const D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };        

    int _layerNum = 0;
public:
    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    void SetLayerNum(const int& layer) {
        _layerNum = layer;

        switch (_layerNum)
        {
        case LAYER_BLUR_X:
            //m_mainPos.x = SCREEN_WIDTH / 2.0f;
            AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_BLURX);
            break;
        case LAYER_BLUR_Y:
            //m_mainPos.y = SCREEN_HEIGHT / 2.0f;
            AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_BLURY);
            break;
        case LAYER_RENDERING_TEXTURE:
            m_mainPos = _screenHalf;
            AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_RENDERING_TEXTURE);
            break;
        default:
            m_mainPos = _screenHalf;
            AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_RENDERING_TEXTURE);
            break;
        }

        Init();
    }
};

