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


	//--�����聪�ɏ���-----------------
	ComponentObject::Init();
}

void CO_Prism::Uninit()
{

	//--�����聪�ɏ���-----------------
	ComponentObject::Uninit();
}

void CO_Prism::Update()
{

	//--�����聪�ɏ���-----------------
	ComponentObject::Update();
}

void CO_Prism::Draw()
{

	//--�����聪�ɏ���-----------------
	ComponentObject::Draw();
}

void CO_Prism::DrawImgui()
{

	//--�����聪�ɏ���-----------------
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
	// �d����1�ȏ㍇�����ꍇ
	if (index > 0) {
		// �C���f�b�N�X��t�������āA������x�d������
		if (_isDuplication[name + std::to_string(index)])
		{
			index++;
			return IsDuplicationName(name, index);
		}

		_isDuplication[name + std::to_string(index)] = true;
		return name + std::to_string(index);
	}

	// �d�����Ȃ��ꍇ
	if (_isDuplication[name])
	{
		index++;
		return IsDuplicationName(name, index);
	}
	
	_isDuplication[name] = true;

	return name;
}
