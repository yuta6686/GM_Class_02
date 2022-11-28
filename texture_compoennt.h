#pragma once
/** ---------------------------------------------------------
 *  [texture_compoennt.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/28
 * ------------------------summary--------------------------
 * @brief  テクスチャをセットするコンポーネント
 ** ---------------------------------------------------------*/
#include "component.h"
class TextureComponent :
    public Component
{
    std::shared_ptr<Texture> _texture;
public:    

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

    void SetTextureAndSlot(const std::string& fileName,
        const int& texSlot = 0,
        const bool& flag=false);
};

