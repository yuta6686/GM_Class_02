#pragma once
#include "gameObject.h"
#include "component_object.h"
class RenderingTexture :
    public ComponentObject
{
private:
    int _blurNum = 0;
public:
    inline static const float BLUR_X_SCREEN = SCREEN_WIDTH / 2.0f;
    inline static const float BLUR_Y_SCREEN = SCREEN_HEIGHT / 2.0f;

    inline static const UINT BLUR_NUM = 4;

    std::shared_ptr <VertexShader>  _blurXVertexShader;
    std::shared_ptr <VertexShader>  _blurYVertexShader;
    std::shared_ptr <VertexShader>  _copyVertexShader;
    std::shared_ptr<PixelShader>    _blurPixelShader;
    std::shared_ptr<PixelShader>    _copyPixelShader;

    VERTEX_3D m_vertex[4];
    ID3D11Buffer* m_VertexBuffer = NULL;

    inline static const D3DXVECTOR3 _screenHalf =
    { SCREEN_WIDTH ,SCREEN_HEIGHT,0.0f };

    D3DXVECTOR3 m_mainPos = _screenHalf;
    inline static const D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };        

    int _layerNum = 0;    

    inline static const std::string _typeName = "Switch Blur";
public:
    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()override;
        

    void SetLayerNum(const int& layer) {
        _layerNum = layer;

        switch (_layerNum)
        {
        case LAYER_LUMINANCE:
            // TODO // https://yuta6686.atlassian.net/browse/AS-41 輝度抽出用シェーダー追加する
            AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_LUMINANCE);
            break;
        //case LAYER_BLUR_X:
        //    //m_mainPos.x = SCREEN_WIDTH / 2.0f;
        //    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_BLURX);
        //    break;
        //case LAYER_BLUR_Y:
        //    //m_mainPos.y = SCREEN_HEIGHT / 2.0f;
        //    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_BLURY);
        //    break;
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

