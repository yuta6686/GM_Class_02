#pragma once
#include "polygon2D.h"


class Manager
{
public:
	static Manager& Instance();

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
	Manager(Manager&&) = delete;
	Manager& operator=(Manager&&) = delete;
private:	
	Manager() = default;
	~Manager() = default;

	static void Draw2D();
	static void Draw3D();


};