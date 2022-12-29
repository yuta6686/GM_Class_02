#include "stdafx.h"
#include "prism_factory.h"
#include "co_prism.h"
#include "blink_position_component.h"



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

	auto prismGenerator = _scene->AddGameObject<PrismGenerator>(LAYER_3D);

	prismGenerator->AddPrisms(transform);
}

void PrismGenerator::Init()
{
	AddComponent<ImGuiComponent>(COMLAYER_FIRST)->SetIsUse(true);

	_scene = Manager::GetScene();

	ComponentObject::Init();
}

void PrismGenerator::Uninit()
{
	SerializeBackUp_End();

	ComponentObject::Uninit();
}

void PrismGenerator::DrawImgui()
{

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


void PrismGenerator::Generate()
{
	if (ImGui::TreeNode("Generate")) {
		static PrismGenerateParameter param;
		param._scale = { 1.0f,1.0f,1.0f };
		param._speed = 0.01f;
		param._min = -5.0f;
		param._max = 5.0f;
		param._axis = AXIS_Y;
		param._fileName_EnvironmentMapping =
			"asset\\texture\\swordOfKirito.png";

		static char buff[1024];
		ImGui::InputText("name", buff, 1024);
		param._name = buff;


		if (ImGui::TreeNode("##1", "Position x:%.2f y:%.2f z:%.2f", param._position.x, param._position.y, param._position.z))
		{
			ImGui::SliderFloat("x", &param._position.x, -_pos_max, _pos_max);
			ImGui::SliderFloat("y", &param._position.y, -_pos_max, _pos_max);
			ImGui::SliderFloat("z", &param._position.z, -_pos_max, _pos_max);
			ImGui::TreePop();
		}

		//ImGui::SliderFloat3();
		ImGui::DragFloat("x", &param._position.x,0.1f);
		ImGui::SameLine();
		ImGui::DragFloat("y", &param._position.y,0.1f);
		ImGui::SameLine();
		ImGui::DragFloat("z", &param._position.z, 0.1f);		
			
		if (ImGui::TreeNode("##2", "Rotation x:%.2f y:%.2f z:%.2f", param._rotation.x, param._rotation.y, param._rotation.z))
		{
			ImGui::SliderFloat("x", &param._rotation.x, -D3DX_PI, D3DX_PI);
			ImGui::SliderFloat("y", &param._rotation.y, -D3DX_PI, D3DX_PI);
			ImGui::SliderFloat("z", &param._rotation.z, -D3DX_PI, D3DX_PI);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("##3", "Scale x:%.2f y:%.2f z:%.2f", param._scale.x, param._scale.y, param._scale.z))
		{
			ImGui::SliderFloat("x", &param._scale.x, 0.0f, 10.0f);
			ImGui::SliderFloat("y", &param._scale.y, 0.0f, 10.0f);
			ImGui::SliderFloat("z", &param._scale.z, 0.0f, 10.0f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("##4", "Blink speed:[%.2f] min:[%.2f] max:[%.2f] axis:[%d]"))
		{
			ImGui::SliderFloat("speed", &param._speed, 0.0f, 2.0f);
			ImGui::SliderFloat("min", &param._min, -10.0f, 10.0f);
			ImGui::SliderFloat("max", &param._max, -10.0f, 10.0f);
			ImGui::SliderInt("axis", &param._axis, AXIS_X, AXIS_XYZ);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("##5", "FileName: [%s]", param._fileName_EnvironmentMapping.c_str()))
		{
			static char* buffFileName;
			buffFileName = (char*)param._fileName_EnvironmentMapping.c_str();

			ImGui::InputText("FlieName", buffFileName, 1024);

			ImGui::TreePop();
		}




		ImGui::Separator();

		MyImgui::PushStyleColor_Button(0.5f);

		if (ImGui::Button("Prism Generate"))
		{
			AddPrism(param);
		}
		ImGui::PopStyleColor(3);
		ImGui::TreePop();
	}
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

		param._name.resize(1024);
		ImGui::InputText("name", param._name.data(), 1024);

		ImGui::Separator();


		if (ImGui::TreeNode("##1", "Position x:%.2f y:%.2f z:%.2f", param._position.x, param._position.y, param._position.z))
		{
			ImGui::SliderFloat("x", &param._position.x, -_pos_max, _pos_max);
			ImGui::SliderFloat("y", &param._position.y, -_pos_max, _pos_max);
			ImGui::SliderFloat("z", &param._position.z, -_pos_max, _pos_max);
			ImGui::TreePop();
		}
		ImGui::Separator();
		if (ImGui::TreeNode("##2", "Rotation x:%.2f y:%.2f z:%.2f", param._rotation.x, param._rotation.y, param._rotation.z))
		{
			ImGui::SliderFloat("x", &param._rotation.x, -D3DX_PI, D3DX_PI);
			ImGui::SliderFloat("y", &param._rotation.y, -D3DX_PI, D3DX_PI);
			ImGui::SliderFloat("z", &param._rotation.z, -D3DX_PI, D3DX_PI);
			ImGui::TreePop();
		}
		ImGui::Separator();
		if (ImGui::TreeNode("##3", "Scale x:%.2f y:%.2f z:%.2f", param._scale.x, param._scale.y, param._scale.z))
		{
			ImGui::SliderFloat("x", &param._scale.x, 0.0f, 10.0f);
			ImGui::SliderFloat("y", &param._scale.y, 0.0f, 10.0f);
			ImGui::SliderFloat("z", &param._scale.z, 0.0f, 10.0f);
			ImGui::TreePop();
		}
		ImGui::Separator();

		if (ImGui::TreeNode("##4", "Blink speed:[%.2f] min:[%.2f] max:[%.2f] axis:[%d]"))
		{
			ImGui::SliderFloat("speed", &param._speed, 0.0f, 0.1f);
			ImGui::SliderFloat("min", &param._min, -10.0f, 10.0f);
			ImGui::SliderFloat("max", &param._max, -10.0f, 10.0f);
			ImGui::SliderInt("axis", &param._axis, AXIS_X, AXIS_XYZ);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("##5", "FileName: [%s]", param._fileName_EnvironmentMapping.c_str()))
		{
			static char* buffFileName;
			buffFileName = (char*)param._fileName_EnvironmentMapping.c_str();

			ImGui::InputText("FlieName", buffFileName, 1024);

			ImGui::TreePop();
		}

		MyImgui::PushStyleColor_Button(0.0f);
		if (ImGui::Button("Remove"))
		{
			_prism[_itemCurrent]->SetDestroy();
			GetPrismObjects();
			UpdatePrism();
		}
		ImGui::PopStyleColor(3);

		_prism[_itemCurrent]->ResetMyName();
		param.SetPrism(_prism[_itemCurrent]);

		ImGui::TreePop();
	}
}


