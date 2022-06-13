#pragma once
#include "Enemy.h"
class EnemyFactory
{
public:
	template <typename T>
	static Enemy_Interface* Create() 
	{
		Enemy_Interface* pEnemy = new T();

		pEnemy->SetMaxHp(50);		

		return pEnemy;
	}


};
