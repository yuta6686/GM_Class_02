#pragma once
#include "gameObject.h"

class Scene;
class Cube2D;


class Collision2D :public GameObject
{
private:

	static bool AxisOfSeparationAe1(Cube2D& c1, Cube2D& c2);
	static bool AxisOfSeparationAe2(Cube2D& c1, Cube2D& c2);
	static bool AxisOfSeparationBe1(Cube2D& c1, Cube2D& c2);
	static bool AxisOfSeparationBe2(Cube2D& c1, Cube2D& c2);
	
public:
	inline static const float BOUND_CONST = 1.0f;

	static bool BallHitCcheck(Cube2D& c1, Cube2D& c2);
	
	//---------------------------------------------------------------------------------------
	// 三平方の定理から2点の距離の2乗を計算
	//---------------------------------------------------------------------------------------
	float Distance2(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2);

	void OnBallHitInverse(Cube2D* c1, Cube2D* c2);

	//---------------------------------------------------------------------------------------
	// ボール衝突処理
	//---------------------------------------------------------------------------------------
	void OnBallHit(Cube2D* b1, Cube2D* b2);


	// GameObject を介して継承されました
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
};

