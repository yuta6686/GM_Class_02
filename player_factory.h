#pragma once
#include "factory.h"
//  ---------------------------------------------------------
//  PlayerFactory [player_factory.h]
//                                  Author: Yuta Yanagisawa
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  �v���C���[����
//  ---------------------------------------------------------

class PlayerFactory :public Factory
{
private:
	void CreateUI();
public:
	// Factory ����Čp������܂���
	virtual void Create() override;
};