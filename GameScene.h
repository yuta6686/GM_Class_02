#pragma once
#include "scene.h"
class GameScene :
    public Scene
{
public:

    void Init();    
    void Uninit();
    void Update();

private:
    void StageCorridorCreate();
};

