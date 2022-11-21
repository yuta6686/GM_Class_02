#pragma once
#include "factory.h"

class UIFactory :public Factory
{
public:
	virtual void Create() override;
};

class UIGameSceneFactory :public Factory
{
public:
	virtual void Create() override;
};