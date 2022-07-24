#pragma once
#include "GameObject.h"
class Scene;
class Player;
class ImGuiObject :
    public GameObject
{
private:
    bool m_PlayerWindow;
    std::shared_ptr<Scene> m_Scene;
    Player* m_Player;
    
public:
    // Component ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;
};

