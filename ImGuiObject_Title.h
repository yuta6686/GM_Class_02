#pragma once
#include "ImGuiObject.h"
#include "player.h"
class ImGuiObject_Title :
    public ImGuiObject
{
	float ROTATION_MIN = -D3DX_PI;
	float ROTATION_MAX = D3DX_PI;
public:
    virtual void Draw()override
    {
		//	Rotation
		{
			D3DXVECTOR3 prot = m_Player->GetRotation();
			float frot[3] = { prot.x,prot.y,prot.z };

			ImGui::SliderFloat("Rotation X:",
				&frot[0], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Rotation Y:",
				&frot[1], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			ImGui::SliderFloat("Rotation Z:",
				&frot[2], ROTATION_MIN, ROTATION_MAX, "%.3f", 1.0f);

			m_Player->SetRotation(frot);
		}
    }
};

