#pragma once
#include "scene.h"
class Audio;
class Transition;
class GameScene :
    public Scene
{
public:

    void Init();    
    
    void Uninit();
    void Update();

    Audio* GetBGM()const { return m_BGM; }
private:
    void StageCorridorCreate();

    class Audio* m_BGM;
    float m_volume = 1.0f;
    float sourceRate = 1.0f;
    float targetRate = 1.0f;

    Transition* m_Fade = nullptr;    
};

