#include "rendering_texture.h"
#include "UserInterfaceComponent.h"


void RenderingTexture::Init()
{

	AddComponent<ShaderComponent>(COMLAYER_SHADER)->
		SetShaderType(SHADER_RENDERING_TEXTURE);

	UserInterfaceComponent* _userInterface = AddComponent<UserInterfaceComponent>(COMLAYER_DRAW);
	_userInterface->SetWidthHeight({ SCREEN_WIDTH,SCREEN_HEIGHT,0.0f });

	AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();


//---------------------------------
	ComponentObject::Init();
}

void RenderingTexture::Uninit()
{

//---------------------------------
	ComponentObject::Uninit();
}

void RenderingTexture::Update()
{

//---------------------------------
	ComponentObject::Update();
}

void RenderingTexture::Draw()
{

//---------------------------------
	ComponentObject::Draw();
}
