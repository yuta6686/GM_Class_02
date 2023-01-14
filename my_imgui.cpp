#include "stdafx.h"

void MyImgui::MyImguiDraw()
{
	_myFlagTree["Test"]["test1"];
	_myFlagTree["Test"]["test2"];
	_myFlagTree["Test"]["test3"];

	
	//ImGui::Begin("Gizmo");
	//ImGuizmo::SetDrawlist();

	//ImGuizmo::DrawGrid();


}

ImVec4 MyImgui::GetHSV(float color, float bright)
{
	return (ImVec4)ImColor::HSV(color, bright, bright);
}


void MyImgui::PushStyleColor_Button(float hue)
{
	ImGui::PushStyleColor(ImGuiCol_Button, GetHSV(hue, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, GetHSV(hue, 0.7f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, GetHSV(hue, 0.8f));
}
