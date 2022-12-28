#pragma once
/** ---------------------------------------------------------
 *  [blink_position_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/12/28
 * ------------------------summary--------------------------
 * @brief  s‚Á‚½‚è—ˆ‚½‚è‚·‚é‚â‚Â
 ** ---------------------------------------------------------*/
#include "blink_component.h"
class BlinkPositionComponent :
    public BlinkComponent
{
private:
    // •Ï”
    bool _isOnce = false;
    D3DXVECTOR3 _initPosition;
private:
    // ŠÖ”
    // 1‰ñ‚¾‚¯Å‰‚Ée‚ÌˆÊ’u‚ğæ“¾
    void SetInitPositionOnce();
public:    
    BlinkPositionComponent() :
        _isOnce(false), 
        _initPosition({ 0.0f,0.0f,0.0f }) 
    {}
    virtual void Update()override;       

};

