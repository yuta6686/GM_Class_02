#pragma once

#include "renderer.h"
class Resource
{
public:
	virtual void Draw()=0;
	virtual void Load(const char* FileName)=0;
	virtual void Unload()=0;
};

