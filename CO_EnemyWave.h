#pragma once
#include "ComponentObject.h"
#include "EnemyWave.h"
#include "EnemyWave_1_1.h"
class CO_EnemyWave :
    public ComponentObject
{
private:
    bool m_IsAllClear = false;

    int m_SceneNum = 1;
    int m_SceneMaxNum = 3;

    int m_WaveNum = 1;
    int m_WaveMaxNum = 3;

    EnemyWave* m_EnemyWave;
public:

    virtual void Init() override 
    {
         m_EnemyWave = new EnemyWave_1_1("asset\\file\\EnemyGenerate1-1.txt");
    }

    virtual void Uninit() override 
    {
        m_EnemyWave->Uninit();
        delete m_EnemyWave;
    }

    virtual void Update() override 
    {
        m_EnemyWave->Update();

        if (m_EnemyWave->GetIsNextWave()) {
            //	次のstateのポインタだけもらう。
            EnemyWave* ew = m_EnemyWave->CreateNextWave();

            //	今のポインタは消す。
            m_EnemyWave->Uninit();
            delete m_EnemyWave;

            //	新しいポインタを作る
            m_EnemyWave = ew;
            m_EnemyWave->Init();
        }

    }

    virtual void Draw() override
    {
        m_EnemyWave->Draw();
    }

    virtual void DrawImgui() override
    {
        m_EnemyWave->DrawImgui();
    }

    void SetSceneAndWaveNum(const int& scene_num, const int& wave_num)
    {
        if (scene_num >= 1 && scene_num <= m_SceneMaxNum) {
            m_SceneNum = scene_num;
        }
        else
        {
            m_SceneNum = 1;
        }
        
        if (wave_num >= 1 && wave_num <= m_WaveNum) {
            m_WaveNum = wave_num;
        }
        else
        {
            m_WaveNum = 1;
        }
    }
};

