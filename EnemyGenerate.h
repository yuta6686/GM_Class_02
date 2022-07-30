#pragma once
#include "gameObject.h"
#include "manager.h"
#include "scene.h"

class EnemyGenerate :
    public GameObject
{
private:
    std::shared_ptr<Scene> m_Scene;
    std::string m_FileName = "asset\\file\\EnemyGenerate";
    std::string m_Extension = ".txt";
    int m_SaveFileIndex = 2;
    int m_LoadFileIndex = 2;
    int m_NowFileNum = 2;
public:    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()override;
};

