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
	ImGui::Begin("test");

	ImVec4 color;
	color.x = m_Diffuse.r;
	color.y = m_Diffuse.g;
	color.z = m_Diffuse.b;
	color.w = m_Diffuse.a;

	ImGui::ColorEdit4("diffuse", (float*)&color);

	m_Diffuse.r = color.x;
	m_Diffuse.g = color.y;
	m_Diffuse.b = color.z;
	m_Diffuse.a = color.w;

	ImGui::End();

	m_Parent->GetComponent<ModelDrawComponent>()->SetDiffuse(m_Diffuse);
}

void ModelColorChangeComponent::Draw()
{
}

void ModelColorChangeComponent::DrawImgui()
{

}
