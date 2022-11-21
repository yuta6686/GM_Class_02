#pragma once
#include "collision_component.h"
#include "gameObject.h"
#include "co_stand.h"
#include "velocity_component.h"
#include "stage_limit_reflect_component.h"
#include "cylinder.h"
class CollisionComponent_Enemy :
    public CollisionComponent
{
public:

    virtual void Update() override
    {
        std::vector<CO_Stand*> stands = IsCollisionXAxis<CO_Stand>();
        StageLimitComponent_Reflect* slcr = m_Parent->GetComponent< StageLimitComponent_Reflect>();

        float ymin = 0.0f;

        if (!stands.empty()) {
            for (auto stand : stands) {

                ymin = (max(0.1f * stand->GetScale().y, ymin));
                break;
            }
        }
        

        std::vector< Cylinder*> cylinders = IsCollisionCylinder();
        if (!cylinders.empty()){
            for (auto cy : cylinders) {

                ymin = (max(cy->GetPosition().y + cy->GetScale().y, ymin));

                break;
            }
        }
        
        slcr->SetYmin(ymin);
    }

private:
    std::vector<Cylinder*> IsCollisionCylinder()
    {
        std::vector<Cylinder*> m_GameObjects;
        std::vector<Cylinder*> ResultObjects;
        m_GameObjects = m_Scene->GetGameObjects<Cylinder>();
        for (auto object : m_GameObjects) {

            D3DXVECTOR3 clyPos = object->GetPosition();
            D3DXVECTOR3 clyScale = object->GetScale();

            D3DXVECTOR3 direction = m_Parent->GetPosition() - clyPos;
            direction.y = 0.0f;

            float length = D3DXVec3Length(&direction);

            if (length < clyScale.x) {
                ResultObjects.push_back(object);
            }
        }

        return ResultObjects;
    }
};

