#pragma once
#include "Resource.h"

class ComputeShader
	: public Resource
{
	ID3D11ComputeShader* mpComputeShader;
public:	
	virtual void Draw() override;

	virtual void Load(const char* FileName) override;

	virtual void Unload() override;

};