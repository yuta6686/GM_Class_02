#include "stdafx.h"
#include "co_prism.h"
#include "blink_component.h"
#include "blink_position_component.h"



void CO_Prism::Init()
{
	AddComponent<TransformInit>(COMLAYER_FIRST);

	AddComponent<MatrixComponent>(COMLAYER_MATRIX);

	AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_ENVIRONMENT_MAPPING);

	_textureComponent =
		AddComponent<TextureComponent>(COMLAYER_DRAW);
	_textureComponent->SetTextureAndSlot("asset\\texture\\swordOfKirito.png", 2);

	AddComponent<ModelDrawComponent>(COMLAYER_DRAW)
		->SetSourcePath("asset\\model\\prism.obj");

	_blinkPositionComponent = AddComponent<BlinkPositionComponent>(COMLAYER_SECOND);
	_blinkPositionComponent->SetParameter(0.01f, -5.0f, 5.0f, AXIS_Y);


	//--これより↑に書く-----------------
	ComponentObject::Init();
}

void CO_Prism::Uninit()
{

	//--これより↑に書く-----------------
	ComponentObject::Uninit();
}

void CO_Prism::Update()
{

	//--これより↑に書く-----------------
	ComponentObject::Update();
}

void CO_Prism::Draw()
{

	//--これより↑に書く-----------------
	ComponentObject::Draw();
}

void CO_Prism::DrawImgui()
{

	//--これより↑に書く-----------------
	ComponentObject::DrawImgui();
}

void CO_Prism::SetName(const std::string& name,bool notJudge)
{
	if (notJudge)
		_name = name;
	else
		_name = IsDuplicationName(name);
}

std::string CO_Prism::GetName() const
{
	return _name;
}
void CO_Prism::ResetMyName()
{
	_isDuplication[_name] = false;
}
std::string CO_Prism::IsDuplicationName(std::string name, int index)
{
	// 重複が1以上合った場合
	if (index > 0) {
		// インデックスを付け加えて、もう一度重複判定
		if (_isDuplication[name + std::to_string(index)])
		{
			index++;
			return IsDuplicationName(name, index);
		}

		_isDuplication[name + std::to_string(index)] = true;
		return name + std::to_string(index);
	}

	// 重複がない場合
	if (_isDuplication[name])
	{
		index++;
		return IsDuplicationName(name, index);
	}
	
	_isDuplication[name] = true;

	return name;
}
