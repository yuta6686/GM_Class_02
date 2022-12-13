#include "count_component.h"

CountComponent::CountComponent()
    : _count(0),
    _countOffset(0),
    _maxCount(60),
    _delay(0),
    _linerReturn0to1(0.0f),
    _in(false),
    _finish(false),
    _inFinish(false)
{
}

void CountComponent::Init() { _count = 0; }

void CountComponent::Uninit() { }

void CountComponent::Update()
{
    if (_in) {
        if (_count + _delay > 0)
        {
            _count--;
        }
        else
        {
            _inFinish = true;
        }


        _linerReturn0to1 = static_cast<float>(min(_count + _delay, _maxCount)) / static_cast<float>(_maxCount);
    }
    else
    {
        //  Å‘å’l‚ÉŽŠ‚Á‚½ --> m_Count >= _delay + _maxCount
        if (_count - _delay > _maxCount)
        {
            _finish = true;
        }
        else
        {
            _count++;
        }


        _linerReturn0to1 = static_cast<float>(max(_count - _delay, 0)) / static_cast<float>(_maxCount);
    }
}

void CountComponent::Draw() { }

void CountComponent::DrawImgui() {  }

void CountComponent::Start(bool in,
    const int& max,
    const int& delay,
    const int& offset) 
{
    _countOffset = offset;
    _maxCount = max;
    _delay = delay;


    _inFinish = false;
    _finish = false;
    _in = in;


    if (_in) {
        _count = _maxCount + _delay - _countOffset;
    }
    else
    {
        _count = _countOffset;
    }
}