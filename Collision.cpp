#include "Collision.h"
#include "Cube2D.h"
#include "scene.h"
#include "manager.h"

bool Collision2D::BallHitCcheck(Cube2D& c1, Cube2D& c2)
{
	float d = Distance2(c1.GetPosition(), c2.GetPosition());
	float r = c1.GetRadius() + c2.GetRadius();

	D3DXVECTOR3 v1 = c1.GetPosition() - c1.GetVel();
	D3DXVECTOR3 v2 = c2.GetPosition() - c2.GetVel();

	//if (Distance2(v1, v2) < d)return false;

	return d < r* r;
}

float Collision2D::Distance2(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2)
{
	float dx = v1.x - v2.x, dy = v1.y - v2.y;
	return dx * dx + dy * dy;
}

void Collision2D::OnBallHitInverse(Cube2D& c1, Cube2D& c2)
{
	D3DXVECTOR3 v1 = c1.GetVel();
	D3DXVECTOR3 v2 = c2.GetVel();

	c1.SetSpeed(v1 * -1.0f);
	c2.SetSpeed(v2 * -1.0f);
}

void Collision2D::OnBallHit(Cube2D* b1, Cube2D* b2)
{
	float e = BOUND_CONST;
	float m1 = b1->GetMass(), m2 = b2->GetMass();

	// �d�S�����ԏՓˎ��̒P�ʃx�N�g�������߂�
	D3DXVECTOR3 center = b2->GetPosition() - b1->GetPosition();
	float len = sqrtf(center.x * center.x + center.y * center.y);
	center /= len;



	// �{�[���̑��x���Փˎ������ɓ��e�����x�N�g��(�^���ʕۑ��������藧��)����ς��狁�߂�
	D3DXVECTOR3 v1 = b1->GetVel(), v2 = b2->GetVel();
	float dot1 = v1.x * center.x + v1.y * center.y;
	float dot2 = v2.x * center.x + v2.y * center.y;

	D3DXVECTOR3 vc1 = center * dot1;
	D3DXVECTOR3 vc2 = center * dot2;



	// �@�Փˎ��ɐ����ȑ��x�x�N�g������(�Փ˂̉e�����󂯂Ȃ�)��ۑ�
	D3DXVECTOR3 vn1 = v1 - vc1;
	D3DXVECTOR3 vn2 = v2 - vc2;




	// �A�Փˎ������̏Փˌ�x�N�g�����^���ʕۑ������狁�߂�
	D3DXVECTOR3 v1d = ((m1 - e * m2) * vc1 + (1 + e) * m2 * vc2) / (m1 + m2);
	D3DXVECTOR3 v2d = ((m2 - e * m1) * vc2 + (1 + e) * m1 * vc1) / (m1 + m2);



	// �@�ƇA�̃x�N�g�����������Č��ʂ𔽉f	
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
	Scene* scene = Manager::GetScene();

	std::vector<Cube2D*> cubes;
	cubes = scene->GetGameObjects<Cube2D>();

	for (int i = 0;i<cubes.size()-1;i++) 
	{
		for (int j = i+1; j < cubes.size(); j++) {
			if (BallHitCcheck(*cubes[i], *cubes[j])) 
			{
				OnBallHit(cubes[i], cubes[j]);
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