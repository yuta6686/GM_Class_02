#pragma once


class MyImgui
{
public:

	inline static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	inline static ImVec4 window_color = ImVec4(0.0f, 0.0f, 0.2f, 0.8f);

	inline static std::map<std::string,bool> _myFlag;

	inline static std::unordered_map<std::string,std::unordered_map<std::string, bool>> _myFlagTree;
	
	static void MyImguiDraw();

};

