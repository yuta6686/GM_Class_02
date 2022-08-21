#pragma once
#include "gameObject.h"
#include "manager.h"
#include "scene.h"
#include "player.h"

class EnemyGenerate :
    public GameObject
{
private:
    std::shared_ptr<Scene> m_Scene;
    std::string m_FileName = "asset\\file\\EnemyGenerate";
    std::string m_Extension = ".txt";
    std::string m_Version = "_EnemyIndex";
    int m_SaveFileIndex = 2;
    int m_LoadFileIndex = 2;
    int m_NowFileNum = 2;
    inline static ImVec4 window_color = ImVec4(0.0f, 0.0f, 0.2f, 0.5f);

    //  Load Stage_Wave
    int m_StageNum = 1;
    int m_WaveNum = 1;
    inline static const int STAGE_NUM_MAX = 3;
    inline static const int WAVE_NUM_MAX = 3;

    //  CircleDeploy
    int m_NumLayer = 1;
    int m_NumLayer_Max = 16;
    float m_Radius = 10.0f;
    float m_Offset = 0.0f;

    bool IsEnemyGenerateMode = false;

    //  GenerateTransform    
    float _scale;
    D3DXVECTOR3 _scale3;
    int _hp;
    int _enemy_index;

    Player* m_Player;
public:    
    void SetEnemyGenerateMode(bool flag);

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()override;

    
};

