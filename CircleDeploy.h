#pragma once
#include "gameObject.h"
#include "scene.h"
#include "manager.h"
#include "CO_3DPloygonTest.h"
class CircleDeploy
{
private:
	inline static float interval = 360.0f / 16.0f;
	inline static D3DXVECTOR3 circlePos = { 0.0f,1.0f,0.0f };
public:

	template <class T>
	inline static std::vector<T*> AddGameObject_CircleDeploy(
		const int& NumLayer,
		const int& MaxNumLayer,		
		const D3DXVECTOR3& center,
		const float& radius)
	{
		std::vector<T*> result;
		std::shared_ptr<Scene> scene = Manager::GetScene();

		interval = 360.0f / static_cast<float>(MaxNumLayer);

		for (int i = 0; i < NumLayer; i++)
		{
			float angle =
				MyMath::GetRadian(static_cast<float>(i * interval));

			circlePos.x = radius * sinf(angle);
			circlePos.z = radius * cosf(angle);

			
			result.push_back(scene->AddGameObject<T>(LAYER_3D));
			
			result[i]->SetPosition(circlePos);
			
		}
		return result;
	}

	
};

