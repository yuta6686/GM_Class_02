#include "rendering_texture.h"
#include "user_interface_component.h"



void RenderingTexture::Init()
{
	_blurXVertexShader =
		ResourceManager<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_TYPE::SHADER_BLURX]);
	_blurYVertexShader =
		ResourceManager<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_TYPE::SHADER_BLURY]);
	_copyVertexShader =
		ResourceManager<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_TYPE::SHADER_RENDERING_TEXTURE]);
	_depthOfFieldVS =
		ResourceManager<VertexShader>::GetResource(VertexShader::GetFileNames()[SHADER_TYPE::SHADER_DEPTH_OF_FIELD]);
		

	_blurPixelShader =
		ResourceManager<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_TYPE::SHADER_BLURX]);
	_copyPixelShader =
		ResourceManager<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_TYPE::SHADER_RENDERING_TEXTURE]);
	_depthOfFieldPS =
		ResourceManager<PixelShader>::GetResource(PixelShader::GetFileNames()[SHADER_TYPE::SHADER_DEPTH_OF_FIELD]);	

	{
		// ���_�f�[�^������
		m_vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[0].Diffuse = m_Color;
		m_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		m_vertex[1].Position = D3DXVECTOR3(m_mainPos.x, 0.0f, 0.0f);
		m_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[1].Diffuse = m_Color;
		m_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		m_vertex[2].Position = D3DXVECTOR3(0.0f, m_mainPos.y, 0.0f);
		m_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[2].Diffuse = m_Color;
		m_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		m_vertex[3].Position = D3DXVECTOR3(m_mainPos.x, m_mainPos.y, 0.0f);
		m_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertex[3].Diffuse = m_Color;
		m_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		//	���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = m_vertex;


		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	D3DXVECTOR2 mainPos = { SCREEN_WIDTH / 4.0f,SCREEN_HEIGHT / 4.0f };

	// ���_�f�[�^������
	_vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertex[0].Diffuse = m_Color;
	_vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	_vertex[1].Position = D3DXVECTOR3(mainPos.x, 0.0f, 0.0f);
	_vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertex[1].Diffuse = m_Color;
	_vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	_vertex[2].Position = D3DXVECTOR3(0.0f, mainPos.y, 0.0f);
	_vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertex[2].Diffuse = m_Color;
	_vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	_vertex[3].Position = D3DXVECTOR3(mainPos.x, mainPos.y, 0.0f);
	_vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertex[3].Diffuse = m_Color;
	_vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = _vertex;


	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);

	m_Position = { 0.0f,0.0f,0.0f };
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Scale = { 1.0f,1.0f,1.0f };

	m_TypeName = "RenderingTexture";

	// RenderingTexture�͕�������̂ň�������悤�ɂ���
	if(auto obj = Manager::GetScene()->GetGameObjects<RenderingTexture>().size() == 0)
	{
		AddComponent<ImGuiComponent>(COMLAYER_FIRST)->SetIsUse(true);	
	}

	MyImgui::_myFlag["RenderingTexture"] = true;

//---------------------------------
	ComponentObject::Init();
}

void RenderingTexture::Uninit()
{
	m_VertexBuffer->Release();
	_vertexBuffer->Release();
//---------------------------------
	ComponentObject::Uninit();
}

void RenderingTexture::Update()
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_H))
	{
		_drawTextureNum = (_drawTextureNum + 1) % (DTN_ALL + 1);
	}
	if (GetKeyboardTrigger(DIK_J))
	{
		_blurNum = (_blurNum + 1) % (BLUR_NUM + 1);
	}

#endif // _DEBUG
//---------------------------------
	ComponentObject::Update();
}

void RenderingTexture::Draw()
{	


	ComponentObject::Draw();

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	Renderer::SetWorldViewProjection2D();

	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale,
		GetScale().x,
		GetScale().y,
		GetScale().z);
	D3DXMatrixRotationYawPitchRoll(&rot,
		GetRotation().x,
		GetRotation().y,
		GetRotation().z);
	D3DXMatrixTranslation(&trans,
		GetPosition().x,
		GetPosition().y,
		GetPosition().z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;


	//�e�N�X�`���ݒ�
	switch (_layerNum)
	{	
	case LAYER_BEGIN:
		Renderer::BeginOfScr();
		return;
		
	case LAYER_LUMINANCE:
		Renderer::BeginLuminance();
		Renderer::SetRenderTexture(false);
		break;
	case LAYER_BLUR:
		// ���������[�v�����ł���悤�ɂ���
		for (UINT i = 0; i < BLUR_NUM; i++) {

			// X���u���[�`��
			{
				Renderer::BeginBlurX();

				// �܂��V�F�[�_�[
				_blurXVertexShader->Draw();
				_blurPixelShader->Draw();

				viewport.Width = RenderingTexture::BLUR_X_SCREEN;

				// ��������[�v�ŕ��򂷂�
				// 0��ڂ�Luminance
				// 1��ڈȍ~��copy��0����2������i - 1
				switch (i)
				{
				case 0:
					Renderer::SetLuminanceTexture();
					break;
				default:
					Renderer::SetCopyTexture(i - 1, 0);
					break;
				}

				Renderer::GetDeviceContext()->RSSetViewports(1, &viewport);


				//�v���~�e�B�u�g�|���W�ݒ�
				Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				//�|���S���`��
				Renderer::GetDeviceContext()->Draw(4, 0);



			}

			// Y���u���[�`��
			{
				Renderer::BeginBlurY();

				// �V�F�[�_�[
				_blurYVertexShader->Draw();
				_blurPixelShader->Draw();


				viewport.Width = RenderingTexture::BLUR_X_SCREEN  ;
				viewport.Height = RenderingTexture::BLUR_Y_SCREEN ;
				Renderer::SetBlurXTexture();

				Renderer::GetDeviceContext()->RSSetViewports(1, &viewport);


				//�v���~�e�B�u�g�|���W�ݒ�
				Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				//�|���S���`��
				Renderer::GetDeviceContext()->Draw(4, 0);

			}

			// �R�s�[�`��
			{
				Renderer::BeginCopyDraw(i);
				if (i > _blurNum)continue;

				_copyVertexShader->Draw();
				_copyPixelShader->Draw();


				viewport.Width = (FLOAT)SCREEN_WIDTH;
				viewport.Height = (FLOAT)SCREEN_HEIGHT;

				Renderer::GetDeviceContext()->RSSetViewports(1, &viewport);

				// �u���[������̃e�N�X�`��
				Renderer::SetBlurYTexture();
				


				//�v���~�e�B�u�g�|���W�ݒ�
				Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				//�|���S���`��
				Renderer::GetDeviceContext()->Draw(4, 0);

				//Renderer::SetRenderTexture(true);

				//// �u�����h���[�h��ʏ�ɒ���
				//Renderer::SetDefaultBlend();
			}
		}
		return;
	
	case LAYER_TO_RENDERING_TEXTURE:
		Renderer::Begin();
		return;
		

	case LAYER_RENDERING_TEXTURE:
		
		switch (_drawTextureNum)
		{			
		case RenderingTexture::DTN_NORMAL_RENDERING_TEXTURE:
		case RenderingTexture::DTN_ALL:
		default:
				Renderer::SetRenderTexture(false);
			break;
		case RenderingTexture::DTN_LUMINANCE:
			Renderer::SetLuminanceTexture();
			break;
		case RenderingTexture::DTN_LUMINANCE_BLUR:
			return;			
		}

		if (MyImgui::_myFlag[_typeName])return;
		break;
	case LAYER_BLOOM:		
		switch (_drawTextureNum)
		{
		case RenderingTexture::DTN_NORMAL_RENDERING_TEXTURE:
		case RenderingTexture::DTN_LUMINANCE:			
			return;
			
		case RenderingTexture::DTN_LUMINANCE_BLUR:
		case RenderingTexture::DTN_ALL:
		default:
			// �R�s�[�����e�N�X�`����S���������ē\��t����̂͂���
			Renderer::SetCopyTexture();

			// ���Z�����ɕύX����
			Renderer::SetAddBlend();
			break;
		}
		break;
	default:
		return;
		break;
	}
	Renderer::GetDeviceContext()->RSSetViewports(1, &viewport);
	

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

	Renderer::SetRenderTexture(true);	


	// �u�����h���[�h��ʏ�ɒ���
	Renderer::SetDefaultBlend();

	if (_layerNum == LAYER_LUMINANCE)return;
	return;

	// ---------------------------------------------------------------
	{


		//���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);


		Renderer::SetWorldViewProjection2D();

		//���[���h�}�g���N�X�ݒ�
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale,
			GetScale().x,
			GetScale().y,
			GetScale().z);
		D3DXMatrixRotationYawPitchRoll(&rot,
			GetRotation().x,
			GetRotation().y,
			GetRotation().z);
		D3DXMatrixTranslation(&trans,
			GetPosition().x,
			GetPosition().y,
			GetPosition().z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);

//#define DOF
#ifdef DOF
		_depthOfFieldPS->Draw();
		_depthOfFieldVS->Draw();
#else
		
		_copyVertexShader->Draw();
		_copyPixelShader->Draw();
		
#endif // DOF
		

		// �r���[�|�[�g�ݒ�
		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)SCREEN_WIDTH;
		viewport.Height = (FLOAT)SCREEN_HEIGHT;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;

		Renderer::GetDeviceContext()->RSSetViewports(1, &viewport);

		Renderer::SetRenderTexture(false);
		Renderer::SetLuminanceTexture();

		//�v���~�e�B�u�g�|���W�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//�|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);

		Renderer::SetRenderTexture(true);

		// �u�����h���[�h��ʏ�ɒ���
		Renderer::SetDefaultBlend();
	}
}

void RenderingTexture::DrawImgui()
{	
	if (MyImgui::_myFlag["RenderingTexture"] && ImGui::CollapsingHeader("RenderingTexture")) {
		ImGui::Checkbox(_typeName.c_str(), &MyImgui::_myFlag[_typeName]);

		static float _strength = 8.0f;

		ImGui::SliderFloat("Blur Strength", &_strength, 0.1f, 100.0f);

		ImGui::SliderInt("Blur NUm", &_blurNum, 0, 3);

		Renderer::SetBlur(_strength);
	}
}

