#include "light.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"

static int g_LightIndex = 0;

Light::Light()
{
    //  ���C�g�̍ő�l���擾
    const int LightNum = Renderer::GetLightNum();

    //  �����̃C���f�b�N�X��������
    m_index = g_LightIndex;

    //  �o�^�����C���f�b�N�X�̐�����
    if (g_LightIndex < LightNum) {
        g_LightIndex++;
    }
    
}

void Light::Init()
{


	// ���C�g������
    InitDirectionLight(m_Light);

    InitPointLight(m_Light);

    InitAmbientLight(m_Light);


	
    Renderer::SetLight(m_Light, m_index);
}

void Light::Uninit()
{
}

void Light::Update()
{
    Scene* scene = Manager::GetScene();
    Camera* camera = scene->GetGameObject<Camera>();
    Player* player = scene->GetGameObject<Player>();


    //m_Light.eyePos = camera->GetPosition();

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

    m_Position += movePos;
    m_Light.ptPosition = { m_Position.x,m_Position.y+50.0f,m_Position.z };

    Renderer::SetLight(m_Light,m_index);
	
}

void Light::Draw()
{
}

void Light::InitDirectionLight(LIGHT& light)
{ 
    // ���C�g�͉E�����瓖�����Ă���
    light.dirDirection.x = 1.0f;
    light.dirDirection.y = -1.0f;
    light.dirDirection.z = -1.0f;
    //light.dirDirection.Normalize();
    D3DXVec3Normalize(&light.dirDirection, &light.dirDirection);

    // ���C�g�̃J���[�͔�
    light.dirColor.x = 1.5f;
    light.dirColor.y = 1.5f;
    light.dirColor.z = 1.5f;

    // ���_�̈ʒu��ݒ肷��
    Scene* scene = Manager::GetScene();
    Camera* camera = scene->GetGameObject<Camera>();
    m_Light.eyePos = camera->GetPosition();

    light.eyePos = camera->GetPositionReference();
}

void Light::InitPointLight(LIGHT& light)
{
    // �|�C���g���C�g�̍��W��ݒ肷��
    light.ptPosition = m_Position;

    // �|�C���g���C�g�̃J���[��ݒ肷��
    light.ptColor.x = 2.0f;
    light.ptColor.y = 0.0f;
    light.ptColor.z = 0.0f;

    // �|�C���g���C�g�̉e���͈͂�ݒ肷��
    light.ptRange = 500.0f;
}

void Light::InitAmbientLight(LIGHT& light)
{
    // �A���r�G���g���C�g
    light.ambientLight.x = 0.3f;
    light.ambientLight.y = 0.3f;
    light.ambientLight.z = 0.3f;
}

