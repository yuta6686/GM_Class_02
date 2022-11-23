


cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}




struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;    
	float3 Dummy;
	
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}

// ���C�g�f�[�^�ɃA�N�Z�X���邽�߂̒萔�o�b�t�@�[��p�ӂ���
cbuffer DirectionLightCb : register(b4)
{
    // �f�B���N�V�������C�g�p�̃f�[�^
    float3 dirDirection; // ���C�g�̕���
    float3 dirColor; // ���C�g�̃J���[

    // �萔�o�b�t�@�[�Ƀ|�C���g���C�g�p�̕ϐ���ǉ�
    float3 ptPosition; // �|�C���g���C�g�̈ʒu
    float3 ptColor; // �|�C���g���C�g�̃J���[
    float ptRange; // �|�C���g���C�g�̉e���͈�

    // step-5 �X�|�b�g���C�g�̃f�[�^�ɃA�N�Z�X���邽�߂̕ϐ���ǉ�����

    float3 eyePos; // ���_�̈ʒu
    float3 ambientLight; // �A���r�G���g���C�g
};

cbuffer Valiable : register(b5)
{
    float monochoromRate;
    float pad1;
    float pad2;
    float pad3;
}

cbuffer CBBlur : register(b6)
{
    float4 weight[2];
}


//struct LIGHT
//{
//	bool Enable;
//	bool3 Dummy;
//	float4 Direction;
//	float4 Diffuse;
//	float4 Ambient;
//    float3 EyePos;
    
//};

//cbuffer LightBuffer : register(b6)
//{
//	LIGHT Light;
//}

//struct POINT_LIGHT
//{
//    bool Enable;
//    bool3 Dummy;
//    float4 Direction;
//    float4 Diffuse;
//    float4 Ambient;
//    float3 EyePos;
    
//    float3 ptPosition;
//    float ptRange;
//    float4 ptColor;
//};

//cbuffer LightBuffer : register(b5)
//{
//    POINT_LIGHT ptLight;
//}






struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
    float3 tangent      : TANGENT;
    float3 biNormal     : BINORMAL;
};

struct PS_BlurIN
{
    float4 pos : SV_POSITION;
    float4 tex0 : TEXCOORD0;
    float4 tex1 : TEXCOORD1;
    float4 tex2 : TEXCOORD2;
    float4 tex3 : TEXCOORD3;
    float4 tex4 : TEXCOORD4;
    float4 tex5 : TEXCOORD5;
    float4 tex6 : TEXCOORD6;
    float4 tex7 : TEXCOORD7;
};

struct PS_IN
{
	float4 Position		: SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
    float3 worldPos		: TEXCOORD1;
    float3 tangent      : TANGENT;
    float3 biNormal     : BINORMAL;
};
