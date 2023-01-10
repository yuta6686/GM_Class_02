#include "vertex_changer_color_component.h"
#include "polygon3d_component.h"

void VertexChangerComponent_Color::Init()
{
}

void VertexChangerComponent_Color::Uninit()
{
}

void VertexChangerComponent_Color::Update()
{
}

void VertexChangerComponent_Color::DrawImgui()
{
}
void VertexChangerComponent_Color::Draw()
{
    m_Parent->GetComponent<Polygon3DComponent>()->ChangeVertexDraw(m_Color);
}
