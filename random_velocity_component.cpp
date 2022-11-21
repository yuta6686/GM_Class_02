#include "random_velocity_component.h"

void RandomVelocityComponent::Init() 
{
    m_Velocities = m_Parent->GetComponents<VelocityComponent>();

    m_RandomVector = MyMath::VEC3Random(-1.0f, 1.0f);
    m_RandomVector.y = 0.0f;

    for (auto vel : m_Velocities)
    {
        vel->m_Velocity = m_RandomVector * m_Speed;
        break;
    }
}