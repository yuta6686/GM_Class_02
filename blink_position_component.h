#pragma once
/** ---------------------------------------------------------
 *  [blink_position_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/12/28
 * ------------------------summary--------------------------
 * @brief  行ったり来たりするやつ
 ** ---------------------------------------------------------*/
#include "blink_component.h"
class BlinkPositionComponent :
    public BlinkComponent
{
private:
    // 変数
    bool _isOnce = false;
    D3DXVECTOR3 _initPosition;
private:
    // 関数
    // 1回だけ最初に親の位置を取得
    void SetInitPositionOnce();
public:    
    BlinkPositionComponent() :
        _isOnce(false), 
        _initPosition({ 0.0f,0.0f,0.0f }) 
    {}
    virtual void Update()override;       

};

