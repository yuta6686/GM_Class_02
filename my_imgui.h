#pragma once
//
//class MyTree {
//
//	std::map<MyTree, bool> _myFlag;
//	std::string _id;
//public:
//
//	MyTree(std::string id) :_id(id) {}
//
//	bool GetFlag(std::string id) { ; }
//
//	void AddChild(std::string id, bool flag)
//	{
//		_myFlag[id] = flag;
//	}
//
//};

class MyImgui
{
public:
#ifdef _DEBUG
	// Our state
	inline static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	inline static ImVec4 window_color = ImVec4(0.0f, 0.0f, 0.2f, 0.8f);

#endif // _DEBUG
	inline static std::map<std::string,bool> _myFlag;
	// inline static MyTree _myTree;
};

