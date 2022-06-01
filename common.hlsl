


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




struct LIGHT
{
	bool Enable;
	bool3 Dummy;
    
	// ディレクションライト用のデータ
    float4 dirDirection; // ライトの方向
    float4 dirColor; // ライトのカラー

    // step-6 定数バッファーにポイントライト用の変数を追加
    float3 ptPosition;
    float3 ptColor;
    float ptRange;

    float3 eyePos; // 視点の位置
    float3 ambientLight; // アンビエントライト
};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}





struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};


struct PS_IN
{
	float4 Position		: SV_POSITION;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};
