


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

// ライトデータにアクセスするための定数バッファーを用意する
cbuffer DirectionLightCb : register(b4)
{
    // ディレクションライト用のデータ
    float3 dirDirection; // ライトの方向
    float3 dirColor; // ライトのカラー

    // 定数バッファーにポイントライト用の変数を追加
    float3 ptPosition; // ポイントライトの位置
    float3 ptColor; // ポイントライトのカラー
    float ptRange; // ポイントライトの影響範囲

    // step-5 スポットライトのデータにアクセスするための変数を追加する

    float3 eyePos; // 視点の位置
    float3 ambientLight; // アンビエントライト
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

// 定数
static const float PI = 3.1415926f;


// ベックマン分布を計算する
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
    return D;
}

// フレネルを計算。Schlick近似を使用
float SpcFresnel(float f0, float u)
{
    return f0 + (1 - f0) * pow(1 - u, 5);
}

// Cook-Torranceモデルの鏡面反射を計算
float CookTorranceSpecular(float3 L, float3 V, float3 N, float metallic)
{
    float microfacet = 0.76f;
    
    // 金属度を垂直入射のときのフレネル反射率として扱う
    // 金属度が高いほどフレネル反射は大きくなる
    float f0 = metallic;
    
    /// ライトに向かうベクトルと視線に向かうベクトルのハーフベクトル
    float3 H = normalize(L + V);
    
    // 各種ベクトルがどれくらい似ているかを内積を利用して求める
    float NdotH = clamp(dot(N, H), 0.01f, 0.99f);
    float VdotH = clamp(dot(V, H), 0.01f, 0.99f);
    float NdotL = clamp(dot(N, L), 0.01f, 0.99f);
    float NdotV = clamp(dot(N, V), 0.01f, 0.99f);

    // D項をベックマン分布を用いて計算する
    float D = Beckmann(microfacet, NdotH);
    
    float F = SpcFresnel(f0, VdotH);
    
    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));
    
    float m = PI * NdotV * NdotH;
    
    return max(F * D * G / m, 0.0f);
}


// N : ノーマル
// L : 光源に向かうベクトル direction?
// V : 視線に向かうベクトル eyevec
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