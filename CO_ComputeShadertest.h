#pragma once
#include "ComponentObject.h"
#include "ComputeShader.h"



struct TEST_IN
{
	int a, b, c;
};

struct TEST_OUT
{
	int a, b, c;
};

class CO_ComputeShadertest
	:public ComponentObject
{
private:
	ComputeShader<TEST_IN,TEST_OUT>* mpComputeShader;
	std::vector<TEST_IN> mvTest;
public:

	virtual void Init()override {
		for (int i = 0; i < 100; i++)
		{
			mvTest.push_back({ i,i,i });
		}
		

		mpComputeShader = AddComponent<ComputeShader<TEST_IN, TEST_OUT>>(COMLAYER_SECOND);

		mpComputeShader->SetInData(".cso",mvTest);

		ComponentObject::Init();
	}

	virtual void  DrawImgui()override
	{
		TEST_OUT* test = mpComputeShader->GetOutData();
		for (int i = 0; i < 100; i++)
		{
			ImGui::Text("a:%d b:%d c:%d",test[i].a,test[i].b,test[i].c );
		}

	}
};