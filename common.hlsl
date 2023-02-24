


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
    float3 depthInView : TEXCOORD2;
};

// �萔
static const float PI = 3.1415926f;


// �x�b�N�}�����z���v�Z����
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
    return D;
}

// �t���l�����v�Z�BSchlick�ߎ����g�p
float SpcFresnel(float f0, float u)
{
    return f0 + (1 - f0) * pow(1 - u, 5);
}

// Cook-Torrance���f���̋��ʔ��˂��v�Z
float CookTorranceSpecular(float3 L, float3 V, float3 N, float metallic)
{
    float microfacet = 0.76f;
    
    // �����x�𐂒����˂̂Ƃ��̃t���l�����˗��Ƃ��Ĉ���
    // �����x�������قǃt���l�����˂͑傫���Ȃ�
    float f0 = metallic;
    
    /// ���C�g�Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g��
    float3 H = normalize(L + V);
    
    // �e��x�N�g�����ǂꂭ�炢���Ă��邩����ς𗘗p���ċ��߂�
    float NdotH = clamp(dot(N, H), 0.01f, 0.99f);
    float VdotH = clamp(dot(V, H), 0.01f, 0.99f);
    float NdotL = clamp(dot(N, L), 0.01f, 0.99f);
    float NdotV = clamp(dot(N, V), 0.01f, 0.99f);

    // D�����x�b�N�}�����z��p���Čv�Z����
    float D = Beckmann(microfacet, NdotH);
    
    float F = SpcFresnel(f0, VdotH);
    
    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));
    
    float m = PI * NdotV * NdotH;
    
    return max(F * D * G / m, 0.0f);
}


// N : �m�[�}��
// L : �����Ɍ������x�N�g�� direction?
// V : �����Ɍ������x�N�g�� eyevec
float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V)
{
    float dotNL = saturate(dot(N, L));
    
    float dotNV = saturate(dot(N, V));
    
    return (dotNL * dotNV);

}

float GetMonochrome(float3 color)
{
    return 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;

}