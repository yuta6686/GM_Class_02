#pragma once
#include "main.h"
#include "ComponentObject.h"
#include "StageLimitDeleteComponent.h"
#include "BulletComponent.h"

class Bullet : public ComponentObject
{
private:

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


		ComponentObject::Init();
	}
	
	void Update();
	
	void Shoot(D3DXVECTOR3 direction, const float& speed) {
		GetComponent< BulletComponent>()->SetVelocity(direction * speed);
	}


};

