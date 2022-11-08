#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_NormalTexture : register(t1);
Texture2D g_PixelNoiseTexture : register(t2);
Texture2D g_Texture2 : register(t3);
SamplerState g_SamplerState : register(s0);

// 定数
static const float PI = 3.1415926f;

// 関数
//float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
//{
    
//}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //  ピクセルの法線を正規化
    float3 normal = normalize(In.Normal);
    normal.x = -g_NormalTexture.Sample(g_SamplerState, In.TexCoord).r;
    normal.y = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).b;
    normal.z = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).g;
    
    normal = normal * 2.0f - 0.5f;
    normal = normalize(normal);
    
    float3 localNormal = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).xyz;
    localNormal = (localNormal - 0.5f) * 2.0f;
    
    normal = In.tangent * localNormal.x + In.biNormal * localNormal.y + normal * localNormal.z;
    
    float4 ratio = g_PixelNoiseTexture.Sample(g_SamplerState, In.TexCoord);
    float4 diffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    float4 diffuse2 = g_Texture2.Sample(g_SamplerState, In.TexCoord);
    float4 resultDiffuse = lerp(diffuse, diffuse2, ratio.r);
    
    float4 albedoColor = diffuse;
    
    float3 specColor = albedoColor;
    
    float metalic = 0.5f;
    
    float smooth = 0.5f;
    
    //  ライト計算
    float light = saturate(dot(In.Normal.xyz, -dirDirection)) / 3.1415926f;
    
    //  カメラからのベクトル
    float3 eyevec = In.WorldPosition.xyz - eyePos.xyz;
    eyevec = normalize(eyevec);
    
    
    
    //  反射ベクトル
    float3 refv = reflect(dirDirection.xyz, normal.xyz);
    refv = normalize(refv);  
    
    //  スペキュラー計算
    float specular = -dot(eyevec,refv);
    specular = saturate(specular);    
    specular = pow(specular, 30.0f);
    
    //  高さで色変える。
    float color_height_diff = In.WorldPosition.y / 5.0f;
   
    color_height_diff = pow(frac(color_height_diff), 4.0f);
    
    color_height_diff -= 1.0f - In.WorldPosition.y / 10.0f;
    color_height_diff = saturate(color_height_diff);

    
    float rim = dot(eyevec, normal.xyz);        
    rim = 1.0f - abs(rim);
    rim = pow(rim, 10) * 2.0f;
    rim = saturate(rim);

//  Diffuse設定            
    outDiffuse = resultDiffuse;
       
    outDiffuse.rgb *= light;
    outDiffuse.a *= In.Diffuse.a;

    outDiffuse.rgb += specular;
    outDiffuse.b += color_height_diff;
       
    outDiffuse.b += rim;    
    outDiffuse.rgb += ambientLight * 1.2f;
    
}