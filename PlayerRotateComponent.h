#pragma once
#include "component.h"
#include "gameObject.h"

class PlayerRotateComponent :
    public Component
{    
private:
	
	inline static const float PLAYER_SPEED = 0.01f;

	inline static const float MOUSE_SPEED_FIRST_X = 500.0f;
	float m_MouseSpeed_X = MOUSE_SPEED_FIRST_X;

	inline static const float MOUSE_SPEED_FIRST_Y = 500.0f;
	float m_MouseSpeed_Y = MOUSE_SPEED_FIRST_Y;
public:

	D3DXVECTOR3 m_CameraRot;

    virtual void Init() override
    {
    }
    virtual void Uninit() override
    {
    }
    virtual void Update() override
    {
		/*if (GetKeyboardPress(DIK_I)) {
			m_CameraRot.y += PLAYER_SPEED / 5;
		}

		if (GetKeyboardPress(DIK_K)) {
			m_CameraRot.y -= PLAYER_SPEED / 5;
		}*/

		if (IsMouseRightPressed()) {
			m_CameraRot.y += GetMouseX() / m_MouseSpeed_Y;

			if (m_CameraRot.x > MyMath::GetRadian(60.0f)) {
				m_CameraRot.x = MyMath::GetRadian(60.0f);
			}
			else if (m_CameraRot.x < MyMath::GetRadian(-60.0f)) {
				m_CameraRot.x = MyMath::GetRadian(-60.0f);
			}
			else {
				m_CameraRot.x += GetMouseY() / m_MouseSpeed_X;
			}
		}

		if (m_CameraRot.y >= D3DX_PI) {
			m_CameraRot.y = -D3DX_PI;
		}

		if (m_CameraRot.y < -D3DX_PI) {
			m_CameraRot.y = D3DX_PI;
		}
							
		m_Parent->SetRotation({ 0.0f,m_CameraRot.y,m_CameraRot.z });
    }
    virtual void Draw() override
    {
    }
    virtual void DrawImgui() override
    {
		ImGui::SliderFloat("Mouse Speed X", &m_MouseSpeed_X, MOUSE_SPEED_FIRST_X, 1000.0f, "%.2f");

		ImGui::SliderFloat("Mouse Speed Y", &m_MouseSpeed_Y, MOUSE_SPEED_FIRST_Y, 1000.0f, "%.2f");
    }
};

