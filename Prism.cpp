#include "prism.h"

#include "resource.h"
#include "vertexShader.h"
#include "pixelShader.h"

void Prism::Init()
{
	// �v���Y���̃o�b�t�@����
	D3D11_BUFFER_DESC bd = {};
	D3D11_SUBRESOURCE_DATA sd = {};

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bd.ByteWidth = sizeof(VERTEX_3D) * _prism_vertex_num; 
	sd.pSysMem = prism_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &_vertexBufferPrism);
	
	// �[�x�ݒ�
	Renderer::SetDepthEnable(true);

//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset\\texture\\yellow\\js_diffuse.dds",
		NULL,
		NULL,
		&_baseTexture,
		NULL);

	assert(_baseTexture);

	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset\\texture\\yellow\\js_normal.dds",
		NULL,
		NULL,
		&_normalTexture,
		NULL);

	assert(_normalTexture);

	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		_textureName.c_str(),
		NULL,
		NULL,
		&_envTexture,
		NULL);

	assert(_envTexture);
	
// �V�F�[�_���[�h
	_vertexShader =
		ResourceManger<VertexShader>::GetResource("env_mapping_vs.cso");

	_pixelShader =
		ResourceManger<PixelShader>::
		GetResource(PixelShader::GetFileNames()[SHADER_ENVIRONMENT_MAPPING]);
}

void Prism::Uninit()
{
	if (_vertexBufferPrism)
	{
		_vertexBufferPrism->Release();
		_vertexBufferPrism = nullptr;
	}

	if (_baseTexture)
	{
		_baseTexture->Release();
		_baseTexture = nullptr;
	}
}

void Prism::Update()
{
	D3DXMATRIX		matRotateX;				// �w����]�}�g���b�N�X
	D3DXMATRIX		matRotateY;				// �x����]�}�g���b�N�X
	D3DXMATRIX		matRotateZ;				// �y����]�}�g���b�N�X
	D3DXMATRIX		matTrans;				// ���s�ړ��}�g���b�N�X
	D3DXMATRIX		matRotation;			// ��]�}�g���b�N�X�i������j
	D3DXVECTOR3		v_norm;					// �@���x�N�g��
	D3DXVECTOR3		v_norm2;				// �@���x�N�g���i��]��j
	D3DXVECTOR3		v_vtx;					// ���f���̒��_�ւ̈ʒu�x�N�g��
	D3DXVECTOR3		v_vtx2;					// ���f���̒��_�ւ̈ʒu�x�N�g���i��]��j
	D3DXVECTOR3		v_view2;				// ���_���王�_�ւ̃x�N�g��
	D3DXVECTOR3		v_ref;					// ���܃x�N�g��
	D3DXVECTOR3		v_tmp;					// �e���|����
	D3DXVECTOR3		bg_norm;				// �a�f�ʂ̖@���x�N�g��
	D3DXVECTOR3		v_pos;					// ���܃x�N�g���ƃe�N�X�`���ʂƂ̌�_
	D3DXVECTOR3		v0, v1, v2;				// �v���Y���ʂ̖@���x�N�g���v�Z�p
	float		ref_rate_v, ref_rate_t;	// ���܃x�N�g���v�Z�p�ꎞ�ϐ�
	float		rrv_rrt, rrv2_rrt2;
	float		ans_InnerProduct;
	float		tmp0;
	float		n;
	int			i;

	const float size = 0.05f;
	g_Prism.size = { size,size,size };

	switch (g_Prism.status)
	{
	case 0:
		// ���f���p�x�A�ʒu�̏�����
		g_Prism.rotation = { 0, 0, 0 };
		g_Prism.position = { 5, 0, 0 };
		

		// �v���Y���ʂ̖@���x�N�g�����v�Z�E�ݒ�
		for (i = 0; i < 8; i++)
		{
			v0 = prism_vertex[i * 3 + 1].Position - prism_vertex[i * 3].Position;
			v1 = prism_vertex[i * 3 + 2].Position - prism_vertex[i * 3].Position;
			D3DXVec3Cross(&v2, &v0, &v1);
			D3DXVec3Normalize(&v2, &v2);	// ���K��
			prism_vertex[i * 3].Normal =
				prism_vertex[i * 3 + 1].Normal =
				prism_vertex[i * 3 + 2].Normal = v2;
		}
		g_Prism.status = 1;
		// THRU
	case 1:
		// �L�[�ɂ�鎋�_�ʒu����уv���Y�����f���̈ړ�
		if (GetAsyncKeyState(VK_UP) & 0x8000) g_Prism.position[1] += 2.0f;	// �J�[�\���i��j
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) g_Prism.position[1] -= 2.0f;	// �J�[�\���i���j
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) g_Prism.position[0] -= 2.0f;	// �J�[�\���i���j
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) g_Prism.position[0] += 2.0f;	// �J�[�\���i�E�j
		// �����I�ɉ�]
		// g_Prism.rotation.z += 0.01f;
		break;
	default:
		break;
	}
	
	// ���[���h�}�g���b�N�X�ݒ� 
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale,
		g_Prism.size.x,
		g_Prism.size.y,
		g_Prism.size.z);
	D3DXMatrixRotationYawPitchRoll(&rot,
		g_Prism.rotation.x,
		g_Prism.rotation.y,
		g_Prism.rotation.z);
	D3DXMatrixTranslation(&trans,
		g_Prism.position.x,
		g_Prism.position.y,
		g_Prism.position.z);
	matWorld = scale * rot * trans;
	
	for (i = 0; i < 3 * 8; i++)		// ���f���͂R���_��8��
	{
		// �v���Y�����f���̒��_�ɂ���@���x�N�g�������[���h��Ԃցu��]�v
		v_norm = prism_vertex[i].Normal;
		D3DXVec3TransformCoord(&v_norm2, &v_norm, &matRotation);
		D3DXVec3Normalize(&v_norm2, &v_norm2);	// ���K��

		// ���f���̒��_�����[���h��Ԃ֕ϊ����A���_�ւ̕����x�N�g�������߂�
		v_vtx = prism_vertex[i].Position;
		D3DXVec3TransformCoord(&v_vtx2, &v_vtx, &matWorld);
		D3DXVECTOR3 cameravec = Manager::GetScene()->GetGameObject<Camera>()->GetPosition();
		D3DXVec3Normalize(&cameravec, &cameravec);
		//cameravec.x = fabs(cameravec.x);
		//cameravec.y = fabs(cameravec.y);
		//cameravec.z = fabs(cameravec.z);

		v_view2 = cameravec - v_vtx2;
		D3DXVec3Normalize(&v_view2, &v_view2);	// ���K��

		//========================================================================
		//
		//    �����Ɉȉ��̂悤�ȃv���O������ǉ�����
		//
		//    ���@���܂̌v�Z��������܃x�N�g�������߂�@��
		//�@�@�P�F���ܗ��i�Q�j��ϐ��ɐݒ�i 1.0 �� 1.2 ���g�p�j
		//�@�@�Q�F���܂̌v�Z�����ɂ���u���ρv�l���v�Z
		//�@�@�@�@�i�g�p����l�͐�ɋ��߂Ă��� v_norm2 �� v_view2 �𗘗p�j
		//�@�@�R�F���ܗ��A�v�Z�l���g���ċ��܃x�N�g�� v_ref �����߂�
		//
		//========================================================================
		// �i�𓚗�j*************************************************************
		// ���܂̌v�Z��������܃x�N�g�������߂�
		ref_rate_v = 1.0f;
		ref_rate_t = 1.2f;
		rrv_rrt = ref_rate_v / ref_rate_t;
		rrv2_rrt2 = (ref_rate_v * ref_rate_v) / (ref_rate_t * ref_rate_t);
		ans_InnerProduct = D3DXVec3Dot(&v_norm2, &v_view2);
		tmp0 = rrv_rrt * ans_InnerProduct - sqrtf(1.0f - rrv2_rrt2 * (1.0f - ans_InnerProduct * ans_InnerProduct));
		v_ref = tmp0 * v_norm2 - rrv_rrt * v_view2;
		//************************************************************************

		// ���܃x�N�g���̐���ƃe�N�X�`���ʂƂ̌�_�����߂�
		//
		// (����)
		// �ʒu�x�N�g��x0�̓_����x�N�g��m�̕����ɒ��������΂��Ƃ�
		// ���ʂ̖@���x�N�g����n�A���ʏ�̔C�ӂ̓_�̈ʒu�x�N�g����x�Ƃ����
		// �����ƕ��ʂ̌�_�̈ʒu�x�N�g����
		//		x0 + ((x-x0)�En / m�En)m	���u�E�v�̓x�N�g�����m�̓���
		// �ŋ��߂���
		// https://risalc.info/src/line-plane-intersection-point.html
		//
		// OpenGL(�E����W�n)��DirectX(������W�n)�̈Ⴂ(Z���t)�ɒ���
		D3DXVECTOR3 cameraForward = Manager::GetScene()->GetGameObject<Camera>()->GetForward();
		D3DXVec3Normalize(&cameraForward, &cameraForward);
		v_tmp = D3DXVECTOR3(0.0f, 0.0f, -80.0f) - v_vtx2;	// �����̒萔�͓K��
		bg_norm = cameraForward * -1.0f;			// �a�f�̃e�N�X�`���ʂ̖@���x�N�g��
		n = D3DXVec3Dot(&v_tmp, &bg_norm) / D3DXVec3Dot(&v_ref, &bg_norm);
		v_pos = v_vtx2 + n * v_ref;

		// ��_���W�����ۂ̃e�N�X�`�����W�ɕϊ�
		prism_vertex[i].TexCoord.x = 0.5f + v_pos.x * 0.001f;
		prism_vertex[i].TexCoord.y = 0.5f + v_pos.y * 0.001f;

		// �e�N�X�`�����W��OpenGL�Ə㉺���t
		prism_vertex[i].TexCoord.y = 1 - prism_vertex[i].TexCoord.y;
	}
}

void Prism::Draw()
{
	// �V�F�[�_
	_vertexShader->Draw();
	_pixelShader->Draw();

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	// ���_�o�b�t�@�X�V
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Renderer::GetDeviceContext()->Map(_vertexBufferPrism, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, prism_vertex, sizeof(VERTEX_3D) * _prism_vertex_num);
	Renderer::GetDeviceContext()->Unmap(_vertexBufferPrism, 0);

	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBufferPrism, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �e�N�X�`���ݒ�
	if (Renderer::_isRenderTexture) {
		Renderer::SetRenderTexture(true);
		Renderer::GetDeviceContext()->VSSetShaderResources(0, 1, &_baseTexture);
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &_baseTexture);
		Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &_normalTexture);
		Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, &_envTexture);
	}
	else
	{
		Renderer::SetRenderTexture(false);
	}

	


	Renderer::SetWorldMatrix(&matWorld);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(_prism_vertex_num, 0);
}

void Prism::DrawImgui()
{
}
