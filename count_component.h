#pragma once
/** ---------------------------------------------------------
 *  CountComponent [count_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/9
 * ------------------------summary--------------------------
 * @brief  
 ** ---------------------------------------------------------*/
#include "component.h"
#include "gameObject.h"
class CountComponent :
    public Component
{
private:
    static const int DEFAULT_MAX_COUNT = 60;
private:
    int _count;
    int _countOffset;
    int _maxCount;
    int _delay;

    float _linerReturn0to1;

    bool _in;    
    bool _finish;
    bool _inFinish;
public:    
    CountComponent();

    /** Start
     * @brief �v���J�n
     * @param "in"      true--> 0����X�^�[�g.false --> 1����X�^�[�g(to 0)
     * @param "max"     �v�����鎞�Ԃ̎w��
     * @param "delay"   �x��
     * @param "offset" �@
     */
    void Start(bool in,
        const int& max = DEFAULT_MAX_COUNT,
        const int& delay = 0,
        const int& offset = 0);

//  Getter--------------------------------------------------------------------    
    int GetCount()const { return max(_count - _delay, 0); }
    float Get0to1Count()const { return _linerReturn0to1; }
    bool GetStart()const { return _in; }
    bool GetFinish()const { return _finish; }
    bool GetInFinist()const { return _inFinish; }

    // Component ����Čp������܂���
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;
};

