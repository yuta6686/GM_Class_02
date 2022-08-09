#include "TitleScene.h"
#include "TitlePolygon.h"
#include "manager.h"
#include "GameScene.h"
#include "camera.h"
#include "Transition.h"
#include "GameObject_Invoke.h"

#include "player.h"
#include "light.h"
#include "ImGuiObject_Title.h"
#include "CircleDeploy.h"
#include "CO_3DPolygon_circle.h"
#include "CO_TitleBackGround.h"
#include "ComponentObjectTest.h"
#include "CO_ToriiBlock.h"
#include "CO_toExit.h"
#include "CO_toGame.h"
#include "ExitScene.h"
#include "CO_Confirmation.h"


void TitleScene::Init()
{
	//	�J����
	AddGameObject<Camera>(LAYER_FIRST);

	//	���C�g
	AddGameObject<Light>(LAYER_FIRST)->SetPosition(D3DXVECTOR3(0, 0, 0));

	//	�v���C���[
	AddGameObject<Player>(LAYER_3D)->SetIsNoMove();
	
	//	�����l�p�����
	{
		D3DXVECTOR3 centerpos = { 0.0f,0.0f,0.0f };
		m_SwitchToScenes = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPloygonTest>(16, 16, centerpos, 20.0f, 0.0f);
		for (auto switchscene : m_SwitchToScenes) {
			switchscene->GetComponent<VertexChangeComponent_ToGame>()->Init();
		}
	}

	//	�㉺�̃s���N�Ɛ̂��
	{
		D3DXVECTOR3 centerpos = { 0.0f,0.0f,0.0f };
		centerpos.y = 10.0f;
		m_Circles.push_back(CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 0.0f));
		std::vector<CO_3DPolygon_circle*> circles = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 180.0f);
		for (CO_3DPolygon_circle* cir : circles) {
			cir->GetComponent<Polygon3DComponent>()->LoadTexture("asset\\texture\\circle_pink.png");
		}
		m_Circles.push_back(circles);

		centerpos.y = -10.0f;
		m_Circles.push_back(CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 0.0f));
		std::vector<CO_3DPolygon_circle*> circles_ = CircleDeploy::AddGameObject_CircleDeploy<CO_3DPolygon_circle>(16, 32, centerpos, 20.0f, 180.0f);
		for (CO_3DPolygon_circle* cir : circles_) {
			cir->GetComponent<Polygon3DComponent>()->LoadTexture("asset\\texture\\circle_pink.png");
		}
		m_Circles.push_back(circles_);
	}

	//	�w�i�̏\��
	AddGameObject< CO_TitleBackGround>(LAYER_3D);

	//	���� Exit
	AddGameObject< CO_ToriiBlock>(LAYER_3D)->SetPosition({ 0.0f,-7.5f,-30.0f });

	//	���� Game
	AddGameObject< CO_ToriiBlock>(LAYER_3D)->SetPosition({ 0.0f,-7.5f,30.0f });

	//	Exit���f��
	auto* exit = AddGameObject < CO_toExit>(LAYER_3D);
	exit->SetPosition({ 0.0f,13.0f,-30.0f });
	exit->SetRotation({ MyMath::GetRadian(180.0f),0.0f,0.0f });
	
	//	Game���f��
	auto* game = AddGameObject < CO_toGame>(LAYER_3D);
	game->SetPosition({ 0.0f,13.0f,30.0f });
	float gameslca = 7.5f;
	game->SetScale({ gameslca ,gameslca ,gameslca });




//	���ɒǉ�
//--����ȍ~�͒ǉ����Ȃ�-------------------------------------------------------------------
	AddGameObject<ImGuiObject_Title>(LAYER_3D);

	m_Fade = AddGameObject<Transition>(LAYER_2D);
	m_Fade->Start(true);
}

void TitleScene::Update()
{
	Scene::Update();

	//	�㉺�̃s���N�Ɛ̂�펞��]--->���Ƃŕʂ̃Q�[���I�u�W�F�N�g�ɂ�点��B
	for (auto circle : m_Circles) {
		for (auto circle2 : circle) {
			D3DXVECTOR3 pos = circle2->GetPosition();

			float nsin = sinf(MyMath::GetRadian(m_Angle));
			float ncos = cosf(MyMath::GetRadian(m_Angle));

			float nx = ncos * pos.x - nsin * pos.z;
			float nz = nsin * pos.x + ncos * pos.z;

			pos.x = nx;
			pos.z = nz;
			circle2->SetPosition(pos);
		}
	}

//	�ȉ��̓V�[���J�ڏ����Ȃ̂ŁA�Q�[���I�u�W�F�N�g�́u�������A��炸�A�������܂����v
	
	//	�Q�[���V�[���ւ̑J�ڏ���
	{
		//	Game�����̎l�p����������Ȃ�true
		bool istogame = false;
		for (auto sts : m_SwitchToScenes)
		{
			if (sts->GetComponent<VertexChangeComponent_ToGame>()->GetIsToGameAndInside())
				istogame = true;
		}

		if (GetKeyboardTrigger(DIK_SPACE) && istogame) {

			m_Fade->Start(false);
		}


		if (m_Fade->GetFinish() && istogame) {
			Manager::SetScene <GameScene>();
			return;
		}
	}


	//	Exit�V�[���ւ̑J�ڏ���
	{
		bool istoexit = false;
		for (auto sts : m_SwitchToScenes)
		{
			if (sts->GetComponent<VertexChangeComponent_ToGame>()->GetIsToExitAndInside()) {
				istoexit = true;
				break;
			}
		}

		//	�m�FUI�̏o��
		if (GetKeyboardTrigger(DIK_SPACE) && istoexit && m_Confirmation == nullptr) {
			m_Confirmation = AddGameObject< CO_Confirmation>(LAYER_2D);
			return;
		}

		//	�m�FUI�̌���-->Yes�̏ꍇ�̃t�F�[�h�X�^�[�g
		if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes())
		{
			m_Fade->Start(false);
		}

		//	�m�FUI�̌���-->No �̏ꍇ�̃t�F�[�h�X�^�[�g
		if (GetKeyboardTrigger(DIK_SPACE) && m_Confirmation != nullptr && m_Confirmation->GetComponent<ConfirmationComponent>()->GetIsYes() == false) {
			m_Confirmation->SetDestroy();
			m_Confirmation = nullptr;
		}


		if (m_Fade->GetFinish() && istoexit) {
			Manager::SetScene <ExitScene>();
			return;
		}
	}

}
