#pragma once
#define IMCOLOR_HSV(col,bright) (ImVec4)ImColor::HSV(col,biright,bright)

class MyImgui
{
public:

	inline static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	inline static ImVec4 window_color = ImVec4(0.0f, 0.0f, 0.2f, 0.8f);

	inline static std::map<std::string,bool> _myFlag;

	inline static std::unordered_map<std::string,std::unordered_map<std::string, bool>> _myFlagTree;	

	static void MyImguiDraw();
	
	// 絶対に ImGui::PopStyleColor(3); をボタン使用後に置く。
	static void PushStyleColor_Button(float hue);

	static ImVec4 GetHSV(float color, float bright);
};

