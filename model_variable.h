#pragma once
#include "model.h"
class Model_variable :
    public Model
{
private:
	D3DXCOLOR m_Diffuse = { 1.0f,1.0f,0.5f,1.0f };
public:
	virtual void Draw()override;
	virtual void Load(const char* FileName)override;
	virtual void Unload()override;

	void SetDiffuse(D3DXCOLOR diff) { 
		m_Diffuse = diff;
	}
};

