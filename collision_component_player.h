#pragma once
#include "collision_component.h"

class CountComponent;
class CollisionComponent_Player :
    public CollisionComponent
{
private:
    bool m_IsCollision = true;
    bool m_IsGenerateMode = false;
    CountComponent* m_Count;
public:
    void SetIsCollision(bool flag) { m_IsCollision = flag; }
    void SetIsGenerateMode(bool flag) { m_IsGenerateMode = flag; }

    virtual void Init()override;
    virtual void Update() override;

    void DrawImgui();
private:
    std::vector<GameObject*> IsCollisionSphere(const int& Layer);
};

