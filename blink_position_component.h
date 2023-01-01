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
    bool _isNoUpdate = false;
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
    void ReturnInitPositionOnce(bool flag = false)
    {
        _isOnce = flag;
    }

    void SetIsNoUpdate(bool flag = true)
    {
        _isNoUpdate = flag;
    }
};

