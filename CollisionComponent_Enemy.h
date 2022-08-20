#pragma once
#include "CollisionComponent.h"
#include "gameObject.h"
#include "CO_Stand.h"
#include "VelocityComponent.h"
#include "StageLimitComponent_Reflect.h"
#include "Cylinder.h"
class CollisionComponent_Enemy :
    public CollisionComponent
{
public:

    virtual void Update() override
    {
        std::vector<CO_Stand*> stands = IsCollisionXAxis<CO_Stand>();
        StageLimitComponent_Reflect* slcr = m_Parent->GetComponent< StageLimitComponent_Reflect>();

        if (stands.empty()) {
            slcr->SetYmin(max(0.0f, slcr->GetYmin()));            
        }
        else {
            for (auto stand : stands) {

                slcr->SetYmin(max(0.1f * stand->GetScale().y, slcr->GetYmin()));
                break;
            }
        }
        

        std::vector< Cylinder*> cylinders = IsCollisionCylinder();
        if (cylinders.empty()) {
            slcr->SetYmin(max(0.0f, slcr->GetYmin()));            
        }
        else {
            for (auto cy : cylinders) {

                slcr->SetYmin(max(cy->GetPosition().y + cy->GetScale().y, slcr->GetYmin()));

                break;
            }
        }
        
    }

};

