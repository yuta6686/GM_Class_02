
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{		
    float4 color = g_Texture.Sample(g_SamplerState, In.TexCoord) * In.Diffuse;
    
    float offsetU = 10.0f / 1980.0f;
    float offsetV = 10.0f / 1080.0f;
    
    // ��e�N�Z������E
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(offsetU, 0.0f));
    
    // ��e�N�Z�����獶
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(-offsetU, 0.0f));
    
    // ��e�N�Z�����牺
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(0.0f, offsetV));
    
    // ��e�N�Z�������
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(0.0f, -offsetV));
    
    // ��e�N�Z������E��
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(offsetU, -offsetV));
    
    // ��e�N�Z������E��
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(offsetU, offsetV));
    
    // ��e�N�Z�����獶��
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(-offsetU, -offsetV));
    
    // ��e�N�Z�����獶��
    color += g_Texture.Sample(g_SamplerState, In.TexCoord + float2(-offsetU, offsetV));
    
    color /= 9.0f;
   
        
    outDiffuse = color;
}
