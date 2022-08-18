#pragma once
#include "main.h"
#include "ComponentObject.h"
#include "StageLimitDeleteComponent.h"
#include "BulletComponent.h"
#include "CollisionComponent_Bullet.h"

class Bullet : public ComponentObject
{
private:
	inline static const float LENGTH_ = 0.2f;
	
public:		
	void Init() {

		AddComponent<TransformInit>(COMLAYER_FIRST);

		AddComponent<ShaderComponent>(COMLAYER_SHADER);

		AddComponent<MatrixComponent>(COMLAYER_MATRIX);

		ModelDrawComponent* mdc =
			new ModelDrawComponent("asset\\model\\arrow.obj");

		AddComponent(mdc, COMLAYER_DRAW);

		AddComponent< ImGuiComponent>(COMLAYER_SECOND);

		auto* sldc = AddComponent< StageLimitDeleteComponent>(COMLAYER_SECOND);
		sldc->SetLimit('x', -200, 200);
		sldc->SetLimit('z', -200, 200);

		AddComponent< BulletComponent>(COMLAYER_SECOND);
		AddComponent< CollisionComponent_Bullet>(COMLAYER_SECOND);
		

		ComponentObject::Init();
	}
	
	
	
	void Shoot(D3DXVECTOR3 direction, const float& speed) {
		GetComponent< BulletComponent>()->SetVelocity(direction * speed);
	}

	float GetLength()override  { return GameObject::GetLength() * LENGTH_; }
};

