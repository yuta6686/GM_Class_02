#include "ModelColorChangeComponent.h"
#include "ModelDrawComponent.h"

void ModelColorChangeComponent::Init()
{
}

void ModelColorChangeComponent::Uninit()
{
}

void ModelColorChangeComponent::Update()
{
	m_Parent->GetComponent<ModelDrawComponent>()->SetDiffuse(m_Diffuse);
}

void ModelColorChangeComponent::Draw()
{
}

void ModelColorChangeComponent::DrawImgui()
{

}
