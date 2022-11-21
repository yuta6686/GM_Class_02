#pragma once
#include "factory.h"
//  ---------------------------------------------------------
//  PlayerFactory [player_factory.h]
//                                  Author: Yuta Yanagisawa
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  プレイヤー生成
//  ---------------------------------------------------------

class PlayerFactory :public Factory
{
private:
	void CreateUI();
public:
	// Factory を介して継承されました
	virtual void Create() override;
};