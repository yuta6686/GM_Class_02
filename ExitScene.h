#pragma once
#include "scene.h"
#include "manager.h"
class ExitScene :
    public Scene
{
public:
    void Init() {
        Manager::SetIsExit(true);
    }
};

