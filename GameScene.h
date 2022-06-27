#pragma once
#include "scene.h"
class Audio;
class GameScene :
    public Scene
{
public:

    void Init();    
    void Uninit();
    void Update();

private:
    void StageCorridorCreate();

    class Audio* m_BGM;
    float m_volume = 1.0f;
    float sourceRate = 1.0f;
    float targetRate = 1.0f;
};

