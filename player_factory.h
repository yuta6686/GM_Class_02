#pragma once
#include "factory.h"
//  ---------------------------------------------------------
//  PlayerFactory [player_factory.h]
//                                  Author: Yuta Yanagisawa
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  ÉvÉåÉCÉÑÅ[ê∂ê¨
//  ---------------------------------------------------------

class PlayerFactory :public Factory
{
private:
	void CreateUI();
public:
	// Factory ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Create() override;
};