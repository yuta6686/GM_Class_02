#pragma once
#include "Component.h"
#include "manager.h"
#include "scene.h"
#include "gameObject.h"

class CollisionComponent :
    public Component
{
protected:
    std::shared_ptr<Scene> m_Scene;
    bool m_IsSphere = false;
    float m_Length = 3.0f;

    bool M_IsCube = false;
    
public:
    // Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override
    {
        m_Scene = Manager::GetScene();
    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {
        
    }

    virtual void Draw() override
    {
    }

    virtual void DrawImgui() override
    {
    }

    void SetIsSphere(bool flag = true) {
        m_IsSphere = flag;
    }

    template<class T>
    std::vector<T*> IsCollisionSphere()
    {
        std::vector<T*> m_GameObjects;
        std::vector<T*> ResultObjects;
        m_GameObjects = m_Scene->GetGameObjects<T>();
        for (auto object : m_GameObjects) {
            D3DXVECTOR3 objectPosition = object->GetPosition();
            D3DXVECTOR3 direction = m_Parent->GetPosition() - objectPosition;
            float length = D3DXVec3Length(&direction);

            if (length < object->GetLength() + m_Parent->GetLength()) {
                ResultObjects.push_back(object);
            }
        }

        return ResultObjects;
    }

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
                objectPosition.x - objectScale.x <= parentPosition.x + parentScale.x //&&
                /*objectPosition.y + objectScale.y <= parentPosition.y - parentScale.y &&
                objectPosition.y - objectScale.y > parentPosition.y + parentScale.y &&
                objectPosition.z + objectScale.z <= parentPosition.z - parentScale.z &&
                objectPosition.z - objectScale.z > parentPosition.z + parentScale.z*/) {
                ResultObjects.push_back(object);
            }
        }

        return ResultObjects;
    }

    std::vector<GameObject*> IsCollisionSphere(const int& Layer)
    {
        std::vector<GameObject*> m_GameObjects;
        std::vector<GameObject*> ResultObjects;
        m_GameObjects = m_Scene->GetGameObjectLayer(Layer);
        for (auto object : m_GameObjects) {
            D3DXVECTOR3 objectPosition = object->GetPosition();
            D3DXVECTOR3 direction = m_Parent->GetPosition() - objectPosition;
            float length = D3DXVec3Length(&direction);

            if (length < object->GetLength() + m_Parent->GetLength()) {
                ResultObjects.push_back(object);
            }
        }

        return ResultObjects;
    }
    
    std::vector<GameObject*> IsCollisionCube(const int& Layer)
    {
        std::vector<GameObject*> m_GameObjects;
        std::vector<GameObject*> ResultObjects;
        m_GameObjects = m_Scene->GetGameObjectLayer(Layer);
        for (auto object : m_GameObjects) {
            D3DXVECTOR3 objectPosition = object->GetPosition();
            D3DXVECTOR3 parentPosition = m_Parent->GetPosition();
            D3DXVECTOR3 objectScale = object->GetScale();
            D3DXVECTOR3 parentScale = m_Parent->GetScale();

            if (objectPosition.x + objectScale.x/6.0f > parentPosition.x - parentScale.x &&
                objectPosition.x - objectScale.x/6.0f <= parentPosition.x + parentScale.x &&
                objectPosition.y + objectScale.y*3.5f >= parentPosition.y - parentScale.y &&
                objectPosition.y - objectScale.y < parentPosition.y + parentScale.y &&
                objectPosition.z + objectScale.z / 6.0f >= parentPosition.z - parentScale.z &&
                objectPosition.z - objectScale.z / 6.0f < parentPosition.z + parentScale.z) {
                ResultObjects.push_back(object);
            }
        }

        return ResultObjects;
    }

   /* template<class T>
    std::vector<T*> IsCollisionCube()
    {
        std::vector<GameObject*> m_GameObjects;
        std::vector<GameObject*> ResultObjects;
        m_GameObjects = m_Scene->GetGameObjects<T>();
        for (auto object : m_GameObjects) {
            D3DXVECTOR3 objectPosition = object->GetPosition();
            D3DXVECTOR3 direction = m_Parent->GetPosition() - objectPosition;
            float length = D3DXVec3Length(&length);

            if (length < len) {
                ResultObjects.push_back(object);
            }
        }

        return ResultObjects;
    }*/
};

