#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_NormalTexture : register(t1);
Texture2D g_PixelNoiseTexture : register(t2);
Texture2D g_Texture2 : register(t3);
SamplerState g_SamplerState : register(s0);

// 定数
static const float PI = 3.1415926f;

// 関数
float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    float3 binSpaceNormal = g_NormalTexture.SampleLevel(g_SamplerState, uv, 0.0f).xyz;
    binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;
    float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;
    return newNormal;
}

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
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));
    float NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));

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

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //  ピクセルの法線を正規化
    float3 normal = GetNormal(In.Normal.xyz, In.tangent, In.biNormal, In.TexCoord);
    //normal.x = -g_NormalTexture.Sample(g_SamplerState, In.TexCoord).r;
    //normal.y = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).b;
    //normal.z = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).g;
    
    normal = normal * 2.0f - 0.5f;
    normal = normalize(normal);
    
    float3 localNormal = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).xyz;
    localNormal = (localNormal - 0.5f) * 2.0f;
    
    normal = In.tangent * localNormal.x + In.biNormal * localNormal.y + normal * localNormal.z;
    
    //float4 ratio = g_PixelNoiseTexture.Sample(g_SamplerState, In.TexCoord);
    //float4 diffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    //float4 diffuse2 = g_Texture2.Sample(g_SamplerState, In.TexCoord);
    //float4 resultDiffuse = lerp(diffuse, diffuse2, ratio.r);
    
    float4 albedoColor = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    float3 specColor = albedoColor;
    
    float metalic = 0.5f;
    
    float smooth = 0.5f;
    
    float toEye = normalize(eyePos.xyz - In.WorldPosition.xyz);
    float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -dirDirection, toEye);
    
    // 正規化Lambert拡散反射
    float NdotL = saturate(dot(normal, -dirDirection));
    float3 lambertDiffuse = dirDirection * NdotL / PI;
    
    // 最終的な拡散反射光を計算する
    float3 diffuse = albedoColor.rgb * diffuseFromFresnel * lambertDiffuse;
    
    // Cook-Torranceモデルを利用した鏡面反射率を計算する
    float3 spec = CookTorranceSpecular(
    -dirDirection, toEye, normal, smooth) * dirColor;
    
    spec *= lerp(float3(1.0, 1.0f, 1.0f), specColor, metalic);
    
    
    //  ライト計算
    float light = saturate(dot(In.Normal.xyz, -dirDirection)) / PI + diffuseFromFresnel;
    
    //  カメラからのベクトル
    float3 eyevec = In.WorldPosition.xyz - eyePos.xyz;
    eyevec = normalize(eyevec);
    
    
    

//  Diffuse設定            
    outDiffuse.rgb = diffuse * (1.0f - smooth) + spec;
    
    
    //outDiffuse.rgb *= light;
    outDiffuse.a = In.Diffuse.a;


    outDiffuse.rgb += ambientLight * 1.2f * albedoColor;
    
}