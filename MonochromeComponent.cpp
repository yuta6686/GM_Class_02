#include "MonochromeComponent.h"
#include "Enemy.h"
#include "ShootBullet_Amass.h"
#include "ShootBullet_Shoot.h"
void MonochromeComponent::Init()
{
    m_VelocityComponents = m_Parent->GetComponents<VelocityComponent>();
    m_Count = m_Parent->AddComponent<CountComponent>(COMLAYER_SECOND);

    VALIABLE m_Valiable = { 0.0f,1.0f,1.0f,1.0f };

    m_Count->Start(true, 1, 0,0);

    m_Scene = Manager::GetScene();

    
}
void MonochromeComponent::Uninit()
{
}
void MonochromeComponent::Update()
{
    VelocityComponent* pvel = m_Parent->GetComponent<VelocityComponent>();
    m_ShootBullet = m_Parent->GetComponent<ShootBulletComponent>()->GetShootBullet();

    m_Enemys = m_Scene->GetGameObjectLayer(LAYER_ENEMY);

    
    int BulletNum = m_BulletNum * 7;

    
    //  GetKeyboardPress(DIK_SPCE)はプレイヤーのVelocityが0より大きかったらにする
    if ((pvel->m_Velocity.y > 0.05f ||
        pvel->m_Velocity.y < -0.05f) &&
        IsMouseLeftTriggered()) //  IsMouseLeftTriggerd() --> ShootBulletがShootBullet_Amassだったら
    {

        m_Count->Start(false, 30, 0,0);

        m_In = true;
        m_VelocityComponents[0]->SetStart(false, 30, 0,0);

        for (auto enemy : m_Enemys) {
            std::vector<VelocityComponent*> vel = enemy->GetComponents<VelocityComponent>();
            for (auto v : vel) {
                v->SetStart(false, 30, 0,0);
            }
        }
    }

    //  !GetKeyboardPress(DIK_SPCE)はプレイヤーのVelocityが止まったらにする。
    //   ImGui::IsMouseReleased(ImGuiMouseButton_Left) --> ShootBulletがShootBullet_Idleだったら
    if (!pvel->GetHasVelocityChanged_Y() &&
        //ImGui::IsMouseReleased(ImGuiMouseButton_Left) &&
        dynamic_cast<ShootBullet_Shoot*>(m_ShootBullet) &&
        m_In)
    {
        m_In = false;
        m_Count->Start(true, 30, BulletNum, 30-m_Count->GetCount());
        m_VelocityComponents[0]->SetStart(true, 30, BulletNum, 30 - m_Count->GetCount());

        for (auto enemy : m_Enemys) {            
            std::vector<VelocityComponent*> vel = enemy->GetComponents<VelocityComponent>();
            for (auto v : vel) {
                v->SetStart(true, 30, BulletNum, 30 - m_Count->GetCount());
            }
        }
    }

    

    m_Valiable.MonochoromeRate = m_Count->Get0to1Count();
    Renderer::SetValiable(m_Valiable);

}
void MonochromeComponent::Draw()
{
}
void MonochromeComponent::DrawImgui() 
{
    ImGui::Text("%d", ImGui::GetKeyIndex(ImGuiKey_Space));
    ImGui::Text("%d", ImGui::GetKeyPressedAmount(ImGuiKey_Space, 0.0f, 1.0f));

}