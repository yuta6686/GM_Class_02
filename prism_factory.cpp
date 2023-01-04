#include "stdafx.h"
#include "prism_factory.h"
#include "co_prism.h"
#include "blink_position_component.h"
#include "chain_of_responsibility.h"


void PrismGenerateParameter::TakeOutPrismParameter(CO_Prism* prism)
{
	BlinkParameter blinkParam = prism->_blinkPositionComponent->GetBlinkParameter();

	_name = prism->GetName();
	_position = prism->GetPosition();
	_rotation = prism->GetRotation();
	_scale = prism->GetScale();
	_speed = blinkParam._speed;
	_min = blinkParam._min;
	_max = blinkParam._max;
	_axis = blinkParam._axis;
	_fileName_EnvironmentMapping = prism->_textureComponent->GetFileName();
}

void PrismGenerateParameter::SetPrism(CO_Prism* prism)
{
	prism->SetName(_name, true);
	prism->SetPosition(_position);
	prism->SetRotation(_rotation);
	prism->SetScale(_scale);
	prism->_blinkPositionComponent->ReturnInitPositionOnce();
	prism->_blinkPositionComponent->
		SetParameter(_speed, _min, _max, (AXIS)_axis);
	prism->_textureComponent->SetTextureAndSlot(_fileName_EnvironmentMapping, 2);
}


//#define SEREALIZE
void PrismFactory::Create()
{
	std::vector<PrismGenerateParameter> transform =
	{
		{
			"name",
			{0.0f,0.0f,0.0f},
			{0.0f,0.0f,0.0f},
			{1.0f,1.0f,1.0f},
			0.01f,-5.0f,5.0f,AXIS_Y,
			"asset\\texture\\swordOfKirito.png",
		},
		{
			"abc",
			{0.0f,3.0f,0.0f},
			{0.0f,0.0f,0.0f},
			{1.0f,1.0f,1.0f},
			0.01f,-5.0f,5.0f,AXIS_Y,
			"asset\\texture\\swordOfKirito.png",
		},
	};


#ifdef SEREALIZE
	// 一旦シリアライズする-->一旦できたので、ImGui側から作れるようにする
	{
		std::ofstream os(PRISM_FILE_NAME, std::ios::out);
		cereal::JSONOutputArchive archiveFile(os);
		serialize(archiveFile, transform);
	}
#else
	// デシリアライズ
	{
		std::ifstream is(PRISM_FILE_NAME, std::ios::in);
		cereal::JSONInputArchive archiveFile(is);
		serialize(archiveFile, transform);
	}

#endif // SEREALIZE

// PrismGeneratorをReleaseで表示しないようにする https://yuta6686.atlassian.net/browse/AS-7
#ifdef _DEBUG
	auto prismGenerator = _scene->AddGameObject<PrismGenerator>(LAYER_3D);

	prismGenerator->AddPrisms(transform);

	
#else	
	PrismGenerator::AddPrismFirst(transform);
#endif // _DEBUG
}

void PrismGenerator::Init()
{
	AddComponent<ImGuiComponent>(COMLAYER_FIRST)->SetIsUse(true);

	_scene = Manager::GetScene();

	_chain = _scene->AddGameObject<ChainOfResponsibility>(LAYER_3D);

	ComponentObject::Init();
}

void PrismGenerator::Update()
{
	// https://yuta6686.atlassian.net/browse/AS-4
	// 左クリックでPrismオブジェクトを選択できるようにする	
	GetPrismObjects();

	if (_prism.size() > _itemCurrent) 
	{
		_prism[_itemCurrent]->SetIsSelect(true);		
	}
	
	

	// 左クリック時のみ
	if (!IsMouseLeftTriggered())return;

	// レイとの判定の準備
	Camera* camera = _scene->GetGameObject<Camera>();	
	D3DXVECTOR3 start, end, vec;
	D3DXMATRIX view, proj;
	view = camera->GetViewMatrix();
	proj = camera->GetProjectionMatrix();

	// 始点位置を変に
	MyMath::transScreenToWorld(&start,
		ImGui::GetIO().MousePos.x,
		ImGui::GetIO().MousePos.y,
		0.0f,
		&view, &proj
	);

	// 終点位置に変換
	MyMath::transScreenToWorld(&end,
		ImGui::GetIO().MousePos.x,
		ImGui::GetIO().MousePos.y,
		1.0f,
		&view, &proj
	);
	vec = end - start;
	D3DXVec3Normalize(&vec, &vec);

	

	// プリズム全部で検証
	// レイと衝突していたら、選択状態にする
	for (unsigned int i=0;i<_prism.size();i++) 
	{
		D3DXVECTOR3 center;
		center = _prism[i]->GetPosition();

		if (MyMath::CalcSphereRayCollision(
			_prism[i]->GetScale().y,
			&center,
			&start,
			&vec,
			&_pos_collision, nullptr
		)) {
			_itemCurrent = i;			
			return;
		}				
	}
}

void PrismGenerator::Uninit()
{
	SerializeBackUp_End();

	ComponentObject::Uninit();
}

void PrismGenerator::DrawImgui()
{
	ImGui::Text("x %.2f", ImGui::GetIO().MousePos.x);
	ImGui::Text("y %.2f", ImGui::GetIO().MousePos.y);
	ImGui::Text("x %.2f y %.2f z %.2f", _pos_collision.x, _pos_collision.y, _pos_collision.z);
	

	if (ImGui::CollapsingHeader("Prism Generate Menu"))
	{
		// 開かれているときは毎フレーム情報を取得する
		// TODO 変更が起こったときだけでいい。
		//      デザインパターンでなにかできればな。
		GetPrismObjects();

		ImGui::Separator();

		// 生成
		Generate();

		ImGui::Separator();


		if (ImGui::TreeNode("cereal")) {

			// シリアライズ
			if (ImGui::Button("Serialize"))
				Serialize();

			// デシリアライズ 追加Version
			if (ImGui::Button("Desirialize Add"))
				DesirializeAdd();

			// デシリアライズ 上書きVersion
			if (ImGui::Button("Desirialize Adress"))
				DesirializeAdress();

			ImGui::TreePop();
		}

		ImGui::Separator();


		// ヒエラルキー
		ShowListBox();

		ImGui::Separator();


		// 情報開示用
		ShowParameter();

		ImGui::Separator();


		// さようならボタン
		if (ImGui::Button("Remove")) {
			RemovePrisms();
		}
	}
}


void PrismGenerator::AddPrisms(std::vector<PrismGenerateParameter> param)
{
	for (PrismGenerateParameter t : param)
	{
		_prismParam.push_back(t);

		auto prism = _scene->AddGameObject<CO_Prism>(LAYER_3D);
		prism->SetName(t._name);
		prism->SetPosition(t._position);
		prism->SetRotation(t._rotation);
		prism->SetScale(t._scale);
		prism->_textureComponent->SetTextureAndSlot(t._fileName_EnvironmentMapping, 2);
		prism->_blinkPositionComponent->SetParameter(t._speed, t._min, t._max, (AXIS)t._axis);
	}
}

void PrismGenerator::AddPrism(PrismGenerateParameter param)
{
	_prismParam.push_back(param);

	CO_Prism* prism = _scene->AddGameObject<CO_Prism>(LAYER_3D);
	prism->SetName(param._name);
	prism->SetPosition(param._position);
	prism->SetRotation(param._rotation);
	prism->SetScale(param._scale);
	prism->_textureComponent->SetTextureAndSlot(param._fileName_EnvironmentMapping, 2);
	prism->_blinkPositionComponent->SetParameter(param._speed, param._min, param._max, (AXIS)param._axis);

}

void PrismGenerator::AddPrismFirst(std::vector<PrismGenerateParameter> param)
{
	CO_Prism* prism = Manager::GetScene()->AddGameObject<CO_Prism>(LAYER_3D);
	for (PrismGenerateParameter t : param)
	{		
		auto prism = Manager::GetScene()->AddGameObject<CO_Prism>(LAYER_3D);
		prism->SetName(t._name);
		prism->SetPosition(t._position);
		prism->SetRotation(t._rotation);
		prism->SetScale(t._scale);
		prism->_textureComponent->SetTextureAndSlot(t._fileName_EnvironmentMapping, 2);
		prism->_blinkPositionComponent->SetParameter(t._speed, t._min, t._max, (AXIS)t._axis);
	}
}

void PrismGenerator::RemovePrisms()
{
	for (auto prism : _prism)
	{
		prism->SetDestroy();
		prism->ResetMyName();
	}
}

void PrismGenerator::GetPrismObjects()
{
	_prism = _scene->GetGameObjects<CO_Prism>();
}

void PrismGenerator::UpdatePrism()
{
	_prismParam.clear();
	for (auto prism : _prism) {
		PrismGenerateParameter param;
		param.TakeOutPrismParameter(prism);
		_prismParam.push_back(param);
	}
}

bool PrismGenerator::IsChangeBlinkParameter(const PrismGenerateParameter& now)
{	
	bool flag = false;

	// 前のフレームとなにかが少しでも変わっていたら
	if(_previousPrismParam != now)
	{
		flag = true;
	}	

	return flag;
}




void PrismGenerator::Generate()
{
	ImGui::Begin("Generate", NULL,
		ImGuiWindowFlags_MenuBar);
	static PrismGenerateParameter param = {
		"prism",
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f},
		0.01f,-5.0f,5.0f,AXIS_Y,
		"asset\\texture\\swordOfKirito.png"
	};

	// "asset\\texture\\enviroment.dds";
	
	ImGui::InputText("name", (char*)param._name.c_str(), 1024);

	// パラメーター
	ImGui::DragFloat3("Position", (float*)&param._position, 0.1f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::DragFloat3("Rotation", (float*)&param._rotation, 0.1f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::DragFloat3("Scale   ", (float*)&param._scale, 0.1f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

	ImGui::DragFloat("Speed", &param._speed, 0.1f, 0.0f, 0.1f);
	ImGui::DragFloat("Min", &param._min, 0.1f, -10.0f, 10.0f);
	ImGui::DragFloat("Max", &param._max, 0.1f, -10.0f, 10.0f);
	ImGui::DragInt("Axis", &param._axis, 1, AXIS_X, AXIS_XYZ);

	// 名前
	static char* buffFileName;
	buffFileName = (char*)param._fileName_EnvironmentMapping.c_str();

	static bool useListBox = false;
	ImGui::Checkbox("Texture use listBox", &useListBox);


	if (useListBox)
	{
		ImGui::ListBox("textures", &PrismTexture::_itemCurrent,
			PrismTexture::_texture.data(), PrismTexture::_texture.size());

		buffFileName = (char*)PrismTexture::GetNowTexture();
	}

	ImGui::InputText("FlieName", buffFileName, 1024);
	param._fileName_EnvironmentMapping = buffFileName;


	ImGui::Separator();

	MyImgui::PushStyleColor_Button(0.5f);

	if (ImGui::Button("Prism Generate"))
	{
		AddPrism(param);
	}
	ImGui::PopStyleColor(3);
	ImGui::End();


}

void PrismGenerator::Serialize()
{
	// _prismParamの更新
	UpdatePrism();

	std::ofstream os(PrismFactory::PRISM_FILE_NAME, std::ios::out);
	cereal::JSONOutputArchive archiveFile(os);
	serialize(archiveFile, _prismParam);
}

void PrismGenerator::SerializeBackUp_End()
{
	// _prismParamの更新
	UpdatePrism();

	std::ofstream os("_prism_backup_end.json", std::ios::out);
	cereal::JSONOutputArchive archiveFile(os);
	serialize(archiveFile, _prismParam);
}

void PrismGenerator::DesirializeAdd()
{
	std::ifstream is(PrismFactory::PRISM_FILE_NAME, std::ios::in);
	cereal::JSONInputArchive archiveFile(is);
	PrismFactory::serialize(archiveFile, _prismParam);
	AddPrisms(_prismParam);
}

void PrismGenerator::DesirializeAdress()
{
	std::ifstream is(PrismFactory::PRISM_FILE_NAME, std::ios::in);
	cereal::JSONInputArchive archiveFile(is);
	PrismFactory::serialize(archiveFile, _prismParam);
	RemovePrisms();
	AddPrisms(_prismParam);
}

void PrismGenerator::ShowListBox()
{
	// _prismParamから_prismのものにする
	std::vector<std::string> str;
	for (auto pr : _prism) {
		str.push_back(pr->GetName());
	}
	std::vector<const char*> names;
	names.resize(_prism.size());
	for (unsigned int i = 0; i < _prism.size(); i++) {
		names[i] = str[i].c_str();
	}

	ImGui::ListBox("prism", &_itemCurrent, names.data(), names.size(), 8);

}

void PrismGenerator::ShowParameter()
{
	if (_prism.size() <= 0)return;
	if (_prism.size() <= _itemCurrent)return;

	// ListBoxで選択されているPrismの情報開示システム
	if (ImGui::TreeNode("##", "Current: [%s]", _prism[_itemCurrent]->GetName().c_str()))
	{

		PrismGenerateParameter param;
		param.TakeOutPrismParameter(_prism[_itemCurrent]);

		// 1フレーム前の検出用 https://yuta6686.atlassian.net/browse/AS-2
		_previousPrismParam = param;

		// ここで_chainにparam渡して変更させればいいのでは？
		_chain->SetCurrentPrism(_prism[_itemCurrent], &param);
		_chain->UpdateHandler();

		param._name.resize(1024);		

		ImGui::InputText("Name", param._name.data(), 1024);

		static bool isnoupdate = false;
		ImGui::Checkbox("Stop Blink",&isnoupdate);
		_prism[_itemCurrent]->_blinkPositionComponent->SetIsNoUpdate(isnoupdate);

		ImGui::DragFloat3("Position", (float*)&param._position, 0.1f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

		ImGui::DragFloat3("Rotation", (float*)&param._rotation, 0.1f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

		ImGui::DragFloat3("Scale", (float*)&param._scale, 0.1f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

		ImGui::DragFloat("Speed", &param._speed, 0.01f, 0.0f, 0.5f);
		ImGui::DragFloat("Min", &param._min, 0.1f, -10.0f, 10.0f);
		ImGui::DragFloat("Max", &param._max, 0.1f, -10.0f, 10.0f);
		ImGui::DragInt("Axis", &param._axis, 1, AXIS_X, AXIS_XYZ);

		static char* buffFileName;
		buffFileName = (char*)param._fileName_EnvironmentMapping.c_str();

	
		ImGui::ListBox("textures", &PrismTexture::_itemCurrent,
			PrismTexture::_texture.data(), PrismTexture::_texture.size());

		buffFileName = (char*)PrismTexture::GetNowTexture();



		param._fileName_EnvironmentMapping = buffFileName;

		MyImgui::PushStyleColor_Button(0.0f);
		if (ImGui::Button("Remove"))
		{
			_prism[_itemCurrent]->SetDestroy();
			GetPrismObjects();
			UpdatePrism();
		}
		ImGui::PopStyleColor(3);



		if (IsChangeBlinkParameter(param)) 
		{
			_prism[_itemCurrent]->ResetMyName();
			_prism[_itemCurrent]->_blinkPositionComponent->SetIsNoUpdate();
			param.SetPrism(_prism[_itemCurrent]);
		}		

		ImGui::TreePop();
	}
}


