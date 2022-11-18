#pragma once
#include "collision_component.h"
#include "gameObject.h"
#include "CO_Stand.h"
#include "velocity_component.h"
#include "stage_limit_reflect_component.h"
#include "Cylinder.h"
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

};

