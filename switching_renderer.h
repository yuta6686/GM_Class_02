#pragma once
#include "gameObject.h"
#include "factory.h"
class SwitchingRenderer :
    public GameObject
{
private:
    int _layerNum = 0;
    
public:   
    SwitchingRenderer() :_layerNum(0) {}

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    void SetLayerNum(const int& layer) { 
        _layerNum = layer; 

    }
};

class SwitchinRendererFactory :public Factory
{
public:            
    // Factory ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Create() override;
};

