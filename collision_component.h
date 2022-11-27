#pragma once
//  ---------------------------------------------------------
//  CollisionComponent [collision_component.h]
//                                  Author: Yuta Yanagisawa
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  - コリジョンコンポーネント
//  ---------------------------------------------------------
#include "component.h"


class CollisionComponent :
    public Component
{
protected:
    std::shared_ptr<Scene> m_Scene;
    
public:
    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;


    template<class T>
    std::vector<T*> IsCollisionXAxis()
    {
        std::vector<T*> m_GameObjects;
        std::vector<T*> ResultObjects;
        m_GameObjects = m_Scene->GetGameObjects<T>();
        for (auto object : m_GameObjects) {
            D3DXVECTOR3 objectPosition = object->GetPosition();   
            D3DXVECTOR3 parentPosition = m_Parent->GetPosition();
            D3DXVECTOR3 objectScale = object->GetScale();
            D3DXVECTOR3 parentScale = m_Parent->GetScale();

            if (objectPosition.x + objectScale.x > parentPosition.x - parentScale.x &&
                objectPosition.x - objectScale.x <= parentPosition.x + parentScale.x) {
                ResultObjects.push_back(object);
            }
        }

        return ResultObjects;
    }                   
};

