#pragma once

#include "renderer.h"
class Resource
{
protected:
	int _textureNum = 0;
	bool _onlySet = false;
public:
	virtual void Draw()=0;
	virtual void Load(const char* FileName)=0;
	virtual void Unload()=0;

	void SetTextureNum(const int& num,const bool& flag = false) 
	{ 
		_textureNum = num; 
		_onlySet = flag;
	}
};

