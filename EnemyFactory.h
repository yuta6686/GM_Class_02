#pragma once
#include "Enemy.h"
class EnemyFactory
{
private:
	inline static int m_EnemyNum = 0;
public:	

	template <typename T>
	static Enemy_Interface* Create() 
	{
		Enemy_Interface* pEnemy = new T();

		pEnemy->SetMaxHp(50);	

		return pEnemy;
	}

	template <typename T>
	static Enemy_Interface* Create(const int& hp)
	{
		Enemy_Interface* pEnemy = new T();

		pEnemy->SetMaxHp(hp);

		return pEnemy;
	}
};

