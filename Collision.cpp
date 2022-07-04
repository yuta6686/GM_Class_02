#include "Collision.h"
#include "Cube2D.h"
#include "scene.h"
#include "manager.h"



bool Collision2D::AxisOfSeparationAe1(Cube2D& c1, Cube2D& c2)
{
	D3DXVECTOR3 L = c1.GetUp();

	D3DXVECTOR3 eb1 = c2.GetRight() * c2.GetMainPos().x;
	D3DXVECTOR3 eb2 = c2.GetUp() * -c2.GetMainPos().y;

	FLOAT ra = c1.GetMainPos().y;
	FLOAT rb = fabs(D3DXVec3Dot(&L, &eb1)) + fabs(D3DXVec3Dot(&L, &eb2));

	D3DXVECTOR3 posdiff = c1.GetPosition() - c2.GetPosition();

	FLOAT Interval = fabs(D3DXVec3Dot(&posdiff, &L));

	if (Interval < ra + rb) {
		return true;
	}

	return false;
}

bool Collision2D::AxisOfSeparationAe2(Cube2D& c1, Cube2D& c2)
{
	D3DXVECTOR3 L = c1.GetRight();

	D3DXVECTOR3 eb1 = c2.GetRight() * c2.GetMainPos().x;
	D3DXVECTOR3 eb2 = c2.GetUp() * -c2.GetMainPos().y;
	
	FLOAT ra = c1.GetMainPos().x;
	FLOAT rb = fabs(D3DXVec3Dot(&L, &eb1)) + fabs(D3DXVec3Dot(&L, &eb2));

	D3DXVECTOR3 posdiff = c1.GetPosition() - c2.GetPosition();

	FLOAT Interval = fabs(D3DXVec3Dot(&posdiff, &L));

	if (Interval < ra + rb) {
		return true;
	}

	return false;
}

bool Collision2D::AxisOfSeparationBe1(Cube2D& c1, Cube2D& c2)
{
	D3DXVECTOR3 L = c2.GetUp();

	D3DXVECTOR3 ea1 = c1.GetRight() * c1.GetMainPos().x;
	D3DXVECTOR3 ea2 = c1.GetUp() * -c1.GetMainPos().y;

	FLOAT ra = fabs(D3DXVec3Dot(&L, &ea1)) + fabs(D3DXVec3Dot(&L, &ea2));
	FLOAT rb = c2.GetMainPos().y;

	D3DXVECTOR3 posdiff = c1.GetPosition() - c2.GetPosition();

	FLOAT Interval = fabs(D3DXVec3Dot(&posdiff, &L));

	if (Interval < ra + rb) {
		return true;
	}

	return false;
}

bool Collision2D::AxisOfSeparationBe2(Cube2D& c1, Cube2D& c2)
{
	D3DXVECTOR3 L = c2.GetRight();

	D3DXVECTOR3 ea1 = c1.GetRight() * c1.GetMainPos().x;
	D3DXVECTOR3 ea2 = c1.GetUp() * -c1.GetMainPos().y;

	FLOAT ra = fabs(D3DXVec3Dot(&L, &ea1)) + fabs(D3DXVec3Dot(&L, &ea2));
	FLOAT rb = c2.GetMainPos().x;

	D3DXVECTOR3 posdiff = c1.GetPosition() - c2.GetPosition();

	FLOAT Interval = fabs(D3DXVec3Dot(&posdiff, &L));

	if (Interval < ra + rb) {
		return true;
	}

	return false;
}

bool Collision2D::BallHitCcheck(Cube2D& c1, Cube2D& c2)
{
	//float d = Distance2(c1.GetPosition(), c2.GetPosition());
	//float r = c1.GetRadius() + c2.GetRadius();

	//D3DXVECTOR3 v1 = c1.GetPosition() - c1.GetVel();
	//D3DXVECTOR3 v2 = c2.GetPosition() - c2.GetVel();

	////if (Distance2(v1, v2) < d)return false;

	//return d < r* r;

	VERTEX_3D* v1 = c1.GetVertex();
	VERTEX_3D* v2 = c2.GetVertex();	

	if (AxisOfSeparationAe1(c1, c2) &&
		AxisOfSeparationAe2(c1, c2) &&
		AxisOfSeparationBe1(c1, c2) &&
		AxisOfSeparationBe2(c1, c2)) {
		return true;
	}

	return false;
}

float Collision2D::Distance2(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2)
{
	float dx = v1.x - v2.x, dy = v1.y - v2.y;
	return dx * dx + dy * dy;
}

void Collision2D::OnBallHitInverse(Cube2D* c1, Cube2D* c2)
{
	D3DXVECTOR3 v1 = c1->GetVel();
	D3DXVECTOR3 v2 = c2->GetVel();

	c1->SetSpeed(v1 * -1.0f);
	c2->SetSpeed(v2 * -1.0f);
}

void Collision2D::OnBallHit(Cube2D* b1, Cube2D* b2)
{
	float e = BOUND_CONST;
	float m1 = b1->GetMass(), m2 = b2->GetMass();

	// 重心を結ぶ衝突軸の単位ベクトルを求める
	D3DXVECTOR3 center = b2->GetPosition() - b1->GetPosition();
	float len = sqrtf(center.x * center.x + center.y * center.y);
	center /= len;



	// ボールの速度を衝突軸方向に投影したベクトル(運動量保存則が成り立つ)を内積から求める
	D3DXVECTOR3 v1 = b1->GetVel(), v2 = b2->GetVel();
	float dot1 = v1.x * center.x + v1.y * center.y;
	float dot2 = v2.x * center.x + v2.y * center.y;

	D3DXVECTOR3 vc1 = center * dot1;
	D3DXVECTOR3 vc2 = center * dot2;



	// ①衝突軸に垂直な速度ベクトル成分(衝突の影響を受けない)を保存
	D3DXVECTOR3 vn1 = v1 - vc1;
	D3DXVECTOR3 vn2 = v2 - vc2;




	// ②衝突軸方向の衝突後ベクトルを運動量保存則から求める
	D3DXVECTOR3 v1d = ((m1 - e * m2) * vc1 + (1 + e) * m2 * vc2) / (m1 + m2);
	D3DXVECTOR3 v2d = ((m2 - e * m1) * vc2 + (1 + e) * m1 * vc1) / (m1 + m2);



	// ①と②のベクトルを合成して結果を反映	
	b1->SetSpeed(v1d + vn1);
	b2->SetSpeed(v2d + vn2);


}

void Collision2D::Init()
{
	
}

void Collision2D::Uninit()
{
}

void Collision2D::Draw()
{
}

void Collision2D::Update()
{
	std::shared_ptr<Scene> scene = Manager::GetScene();

	std::vector<Cube2D*> cubes;
	cubes = scene->GetGameObjects<Cube2D>();

	for (int i = 0;i<cubes.size()-1;i++) 
	{
		for (int j = i+1; j < cubes.size(); j++) {
			if (BallHitCcheck(*cubes[i], *cubes[j])) 
			{
				OnBallHit(cubes[i], cubes[j]);
				// OnBallHitInverse(cubes[i], cubes[j]);
//#ifdef _DEBUG
//				char* str = GetDebugStr();
//				wsprintf(GetDebugStr(), "game");
//				wsprintf(&str[strlen(str)], "true");
//
//				SetWindowText(GetWindow(), GetDebugStr());
//#endif
			}
			else {
//#ifdef _DEBUG
//				char* str = GetDebugStr();
//				wsprintf(GetDebugStr(), "game");
//				wsprintf(&str[strlen(str)], "false");
//
//				SetWindowText(GetWindow(), GetDebugStr());
//#endif
			}
		}
	}
}
