#pragma once
/** ---------------------------------------------------------
 *  [blink_position_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/12/28
 * ------------------------summary--------------------------
 * @brief  �s�����藈���肷����
 ** ---------------------------------------------------------*/
#include "blink_component.h"
class BlinkPositionComponent :
    public BlinkComponent
{
private:
    // �ϐ�
    bool _isOnce = false;
    D3DXVECTOR3 _initPosition;
private:
    // �֐�
    // 1�񂾂��ŏ��ɐe�̈ʒu���擾
    void SetInitPositionOnce();
public:    
    BlinkPositionComponent() :
        _isOnce(false), 
        _initPosition({ 0.0f,0.0f,0.0f }) 
    {}
    virtual void Update()override;       

};

