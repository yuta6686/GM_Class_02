#pragma once
#include "gameObject.h"
#include "manager.h"
#include "scene.h"

class EnemyGenerate :
    public GameObject
{
private:
    std::shared_ptr<Scene> m_Scene;
    std::string m_FileName = "asset\\file\\EnemyGenerate1.txt";
public:    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()override;
};

