
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{		
    float4 color = g_Texture.Sample(g_SamplerState, In.TexCoord) * In.Diffuse;
    
    float offsetU = 10.0f / 1980.0f;
    float offsetV = 10.0f / 1080.0f;
    
    // 基準テクセルから右
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(offsetU, 0.0f));
    
    // 基準テクセルから左
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(-offsetU, 0.0f));
    
    // 基準テクセルから下
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(0.0f, offsetV));
    
    // 基準テクセルから上
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(0.0f, -offsetV));
    
    // 基準テクセルから右上
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(offsetU, -offsetV));
    
    // 基準テクセルから右下
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(offsetU, offsetV));
    
    // 基準テクセルから左上
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(-offsetU, -offsetV));
    
    // 基準テクセルから左下
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(-offsetU, offsetV));
    
    color /= 9.0f;
   
        
    outDiffuse = color;
}
