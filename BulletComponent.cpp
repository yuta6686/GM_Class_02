#include "BulletComponent.h"
#include "gameObject.h"

void BulletComponent::Init()
{
}

void BulletComponent::Uninit()
{
}

void BulletComponent::Update()
{
	//	����
	AddParentPos(m_Velocity);

	m_Velocity *= 0.99f;


	//	y�͏d�͂��l������K�v������̂ŁA������Ƃ킩��Ȃ�

}

void BulletComponent::Draw()
{
}

void BulletComponent::DrawImgui()
{
}

void BulletComponent::AddParentPos(D3DXVECTOR3 addvalue)
{
	D3DXVECTOR3 pos = m_Parent->GetPosition();

	m_Parent->SetPosition(pos + addvalue);
}
