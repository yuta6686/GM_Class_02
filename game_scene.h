#pragma once

#include "scene.h"
class Audio;
class Transition;
class CO_EnemyWave;
class ParticleObject;
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
    void AudioUpdate();

    class Audio* m_BGM;
    float m_volume = 1.0f;
    float sourceRate = 1.0f;
    float targetRate = 1.0f;

    bool m_IsPlayerDeath = false;

    Transition* m_Fade = nullptr;    
    

    CO_EnemyWave* m_EnemyWave = nullptr;
    ParticleObject* m_Particle;
};

