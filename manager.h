#pragma once
#include "polygon2D.h"

class Manager
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	Polygon2D* m_pPoly;
};