#include "stdafx.h"
#include "prism_factory.h"
#include "co_prism.h"
#include "blink_position_component.h"

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

void PrismGenerator::AddPrisms(std::vector<PrismGenerateParameter> param)
{
	_scene = Manager::GetScene();
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

void PrismGenerator::GetPrismObjects()
{
	_prism = _scene->GetGameObjects<CO_Prism>();
}

void PrismGenerator::Init()
{
	AddComponent<ImGuiComponent>(COMLAYER_FIRST)->SetIsUse(true);

	_scene = Manager::GetScene();

	ComponentObject::Init();
}

void PrismGenerator::DrawImgui()
{

	if (ImGui::CollapsingHeader("Prism Generate Menu"))
	{
		static PrismGenerateParameter param;

		static char buff[1024];
		ImGui::InputText("name", buff, 1024);
		param._name = buff;

		if (ImGui::Button("Prism Generate"))
		{

		}


		if (ImGui::Button("Desirialize")) {
			std::ifstream is(PrismFactory::PRISM_FILE_NAME, std::ios::in);
			cereal::JSONInputArchive archiveFile(is);
			PrismFactory::serialize(archiveFile, _prismParam);
			AddPrisms(_prismParam);
		}

		// ListBoxの名前決める
		{
			GetPrismObjects();

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

		// ListBoxで選択されているPrismの情報開示システム
		if (ImGui::TreeNode("##", "Current: [%s]", _prism[_itemCurrent]->GetName().c_str()))
		{
			ImGui::Text("Current: [%s]", _prism[_itemCurrent]->GetName().c_str());

			PrismGenerateParameter param;
			param.SetPrismParameter(_prism[_itemCurrent]);

			
			if (ImGui::TreeNode("##", "Position x:%.2f y:%.2f z:%.2f", param._position.x, param._position.y, param._position.z))
			{
				ImGui::SliderFloat("x", &param._position.x,-10.0,10.0f);
				ImGui::SliderFloat("y", &param._position.y, -10.0, 10.0f);
				ImGui::SliderFloat("z", &param._position.z, -10.0, 10.0f);
				ImGui::TreePop();
			}

			param.SetPrism(_prism[_itemCurrent]);

			ImGui::TreePop();
		}

	}




}

void PrismGenerateParameter::SetPrismParameter(CO_Prism* prism)
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
	prism->SetName(_name,true);
	prism->SetPosition(_position);
	prism->SetRotation(_rotation);
	prism->SetScale(_scale);
	prism->_blinkPositionComponent->ReturnInitPositionOnce();
	prism->_blinkPositionComponent->
		SetParameter(_speed, _min, _max, (AXIS)_axis);
	prism->_textureComponent->SetTextureAndSlot(_fileName_EnvironmentMapping, 2);
}
