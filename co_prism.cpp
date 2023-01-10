#include "stdafx.h"
#include "co_prism.h"
#include "blink_component.h"
#include "blink_position_component.h"



void CO_Prism::InitInternal()
{
	AddComponent<TransformInit>(COMLAYER_FIRST);

	AddComponent<MatrixComponent>(COMLAYER_MATRIX);

	_shaderComponent =
		AddComponent<ShaderComponent>(COMLAYER_SHADER);
	_shaderComponent->SetShaderType(SHADER_ENVIRONMENT_MAPPING);

	_textureComponent =
		AddComponent<TextureComponent>(COMLAYER_DRAW);
	_textureComponent->SetTextureAndSlot("asset\\texture\\swordOfKirito.png", 2);

	AddComponent<ModelDrawComponent>(COMLAYER_DRAW)
		->SetSourcePath("asset\\model\\prism.obj");

	_blinkPositionComponent = AddComponent<BlinkPositionComponent>(COMLAYER_SECOND);
	_blinkPositionComponent->SetParameter(0.01f, -5.0f, 5.0f, AXIS_Y);

	_camera = Manager::GetScene()->GetGameObject<Camera>();
}

void CO_Prism::UninitInternal()
{

}

void CO_Prism::UpdateInternal()
{
	// 選択されていたらシェーダー変える
	if (_isSelect) 
	{
		_shaderComponent->SetShaderType(SHADER_ENVIRONMENT_MAPPING_SELECT);

		_isSelect = false;
	}
	else 
	{
		// 戻す		
		_shaderComponent->SetShaderType(SHADER_ENVIRONMENT_MAPPING);
	}
}

void CO_Prism::DrawInternal()
{

}

void CO_Prism::DrawImguiInternal()
{


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


void CO_Prism::Movement(const D3DXVECTOR3& diff) 
{
	m_Position += diff;
}
void CO_Prism::Rotation(const D3DXVECTOR3& diff)
{
	m_Rotation += diff;
}
void CO_Prism::Scaling(const D3DXVECTOR3& diff)
{
	m_Scale += diff;
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
