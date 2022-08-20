#pragma once
#include "ComponentObject.h"
#include "EnemyWave.h"
#include "EnemyWave_1_1.h"
#include "CO_UI_Quest.h"
#include "CO_UI_Quest_Purpose.h"
#include "CO_UI_Quest_Belt.h"
#include "manager.h"


class CO_EnemyWave :
    public ComponentObject
{
private:
    bool m_IsAllClear = false;
    bool m_IsStageClear = false;

    int m_SceneNum = 1;
    int m_SceneMaxNum = 3;

    int m_WaveNum = 1;
    int m_WaveMaxNum = 3;

    EnemyWave* m_EnemyWave;

    CO_UI_Quest* m_Quest;

    CO_UI_Quest_Purpose* m_Purpose;

    std::vector<CO_UI_Quest_Belt*> m_Belts;

    std::shared_ptr<Scene> m_Scene;

    std::string m_PurposeFileName = "asset\\texture\\wave";
    std::string GetPurposeFileName(const int& index) {
        std::ostringstream oss;
        oss << index;
        return m_PurposeFileName + oss.str() + ".png";
    }
public:
    template <class T>
    void SetEnemyWave(std::string filename)
    {
        if (m_EnemyWave != nullptr) {
            m_EnemyWave->Uninit();
            delete m_EnemyWave;
        }

        m_EnemyWave = new T(filename);
        m_EnemyWave->Init();
    }

    virtual void Init() override 
    {
        m_Scene = Manager::GetScene();

         m_EnemyWave = new EnemyWave_1_1("asset\\file\\EnemyGenerate1-1.txt");

         m_Quest = m_Scene->AddGameObject<CO_UI_Quest>(LAYER_2D);
         m_Purpose = m_Scene->AddGameObject<CO_UI_Quest_Purpose>(LAYER_2D);
         
         float dest_y = 400.0f;
         float dep_y = 800.0f;

         // Quest_Belt[0]
         {             
             m_Belts.push_back(m_Scene->AddGameObject<CO_UI_Quest_Belt>(LAYER_2D));
             m_Belts[0]->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y,0.0f });
             m_Belts[0]->SetDeparture({ -1920.0f / 1.5f,dep_y,0.0f });
             m_Belts[0]->Start(false, 60, 60, true);
         }

         // Quest_Belt[1]
         {
             float sep_y = 200.0f;
             m_Belts.push_back(m_Scene->AddGameObject<CO_UI_Quest_Belt>(LAYER_2D));
             m_Belts[1]->SetDestination({ 1920.0f + 1920.0f / 1.5f,dest_y + sep_y,0.0f });
             m_Belts[1]->SetDeparture({ -1920.0f / 1.5f,dep_y + sep_y,0.0f });
             m_Belts[1]->Start(false, 60, 90, true);
         }

         m_EnemyWave->Init();
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

            int enemy_index = (m_EnemyWave->GetEnemyIndex() % 3);
            m_Purpose->SetTexture(GetPurposeFileName(enemy_index));

            m_Belts[0]->Start(false, 60, 60, true);
            m_Belts[1]->Start(false, 60, 90, true);
            m_Purpose->Start();
            m_Quest->Start();
        }
    }

    virtual void Draw() override
    {
        m_EnemyWave->Draw();
    }

    virtual void DrawImgui() override
    {
        m_EnemyWave->DrawImgui();

        ImGui::Text("Index%d", m_EnemyWave->GetEnemyIndex());
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

    void SetIsStageClear(bool flag = true) { m_IsStageClear = flag; }
    bool GetIsStageClear()const { return m_IsStageClear; }
};

