#pragma once
#include "main.h"
#include "component_object.h"
#include "stage_limit_delete_component.h"
#include "bullet_component.h"
#include "collision_component_bullet.h"

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

