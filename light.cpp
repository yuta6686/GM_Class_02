#include "light.h"
#include "scene.h"

#include "renderer.h"
#include "game_scene.h"
#include "player.h"
#include "camera.h"

static int g_LightIndex = 0;

void Light::Init()
{
    //  ライトの最大値を取得
    const int LightNum = Renderer::GetLightNum();

    //  自分のインデックスを初期化
    m_index = g_LightIndex;

    //  登録されるインデックスの数調整
    //if (g_LightIndex < LightNum) {
    //    g_LightIndex++;
    //}

	// ライト初期化
    InitDirectionLight(m_Light);

    InitPointLight(m_Light);

    InitAmbientLight(m_Light);


	
    Renderer::SetLight(m_Light, m_index);
    
    AddComponent<ImGuiComponent>(COMLAYER_DRAW)->SetIsUse(MyImgui::_myFlag["Light"]);

    ComponentObject::Init();
}

void Light::Uninit()
{
    ComponentObject::Uninit();
}

void Light::Update()
{
    std::shared_ptr<Scene> scene = Manager::GetScene();
    Camera* camera = scene->GetGameObject<Camera>();
    Player* player = scene->GetGameObject<Player>();


    m_Light.eyePos = camera->GetPosition();

    //m_Position = player->GetPosition();

    D3DXVECTOR3 movePos = { 0,0,0 };

    if (GetKeyboardPress(DIK_I)) {
        movePos.z += POINT_LIGHT_SPEED;
    }
    if (GetKeyboardPress(DIK_K)) {
        movePos.z -= POINT_LIGHT_SPEED;
    }

    if (GetKeyboardPress(DIK_J)) {
        movePos.x -= POINT_LIGHT_SPEED;
    }
    if (GetKeyboardPress(DIK_L)) {
        movePos.x += POINT_LIGHT_SPEED;
    }

    if (GetKeyboardPress(DIK_UP)) {
        movePos.y += POINT_LIGHT_SPEED;
    }
    if (GetKeyboardPress(DIK_DOWN)) {
        movePos.y -= POINT_LIGHT_SPEED;
    }

    m_Position += movePos;
    m_Light.ptPosition = { m_Position.x,m_Position.y + 50.0f,m_Position.z };

#ifdef _DEBUG

    /*char* str = GetDebugStr();
    wsprintf(GetDebugStr(), "game");
    wsprintf(&str[strlen(str)], "Light Position.x: %d y:%d z:%d eyePosition.x:%d y:%d z:%d",
        (int)m_Light.ptPosition.x,
        (int)m_Light.ptPosition.y, 
        (int)m_Light.ptPosition.z,
        (int)m_Light.eyePos.x,
        (int)m_Light.eyePos.y,
        (int)m_Light.eyePos.z);

    SetWindowText(GetWindow(), GetDebugStr());*/
#endif    	

    ComponentObject::Update();
}

void Light::Draw()
{
    Renderer::SetLight(m_Light, m_index);

    ComponentObject::Draw();
}

void Light::DrawImgui()
{
    if (!MyImgui::_myFlag["Light"])return;
    if (ImGui::CollapsingHeader("Light")) {
        if (ImGui::TreeNode("Direction")) {
            ImGui::SliderFloat("Direction.x", &m_Light.dirDirection.x, -1.0f, 1.0f);
            ImGui::SliderFloat("Direction.y", &m_Light.dirDirection.y, -1.0f, 1.0f);
            ImGui::SliderFloat("Direction.z", &m_Light.dirDirection.z, -1.0f, 1.0f);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Color")) {
            ImGui::SliderFloat("Color.r", &m_Light.dirColor.x, 0.0f, 1.0f);
            ImGui::SliderFloat("Color.g", &m_Light.dirColor.y, 0.0f, 1.0f);
            ImGui::SliderFloat("Color.b", &m_Light.dirColor.z, 0.0f, 1.0f);
            ImGui::TreePop();
        }

    }
    
}

void Light::InitDirectionLight(LIGHT& light)
{ 
    // ライトは右側から当たっている
    light.dirDirection.x = -1.0f;
    light.dirDirection.y = -1.0f;
    light.dirDirection.z = 2.0f;
    //light.dirDirection.Normalize();
    D3DXVec3Normalize(&light.dirDirection, &light.dirDirection);

    // ライトのカラーは白
    light.dirColor.x = 3.5f;
    light.dirColor.y = 3.5f;
    light.dirColor.z = 3.5f;

    // 視点の位置を設定する
    std::shared_ptr<Scene> scene = Manager::GetScene();
    Camera* camera = scene->GetGameObject<Camera>();
    //m_Light.eyePos = camera->GetPosition();

    light.eyePos = camera->GetPositionReference();

    
}

void Light::InitPointLight(LIGHT& light)
{
    // ポイントライトの座標を設定する
    light.ptPosition = m_Position;

    // ポイントライトのカラーを設定する
    light.ptColor.x = 0.0f;
    light.ptColor.y = 0.0f;
    light.ptColor.z = 0.0f;

    // ポイントライトの影響範囲を設定する
    light.ptRange = 50.0f;
}

void Light::InitAmbientLight(LIGHT& light)
{
    // アンビエントライト
    light.ambientLight.x = 0.3f;
    light.ambientLight.y = 0.3f;
    light.ambientLight.z = 0.3f;
}

