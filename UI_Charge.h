#pragma once
#include "UserInterface.h"
class UI_Charge :
    public UserInterface
{
public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    
};

