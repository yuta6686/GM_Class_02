#pragma once
#include "scene.h"

class ExitScene :
    public Scene
{
public:
    void Init() {
        Manager::SetIsExit(true);
    }
};

