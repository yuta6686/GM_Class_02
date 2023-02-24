
#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_Texture1: register(t1);
Texture2D g_Texture2: register(t2);
Texture2D g_Texture3: register(t3);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 color = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    color += g_Texture1.Sample(g_SamplerState, In.TexCoord);
    color += g_Texture2.Sample(g_SamplerState, In.TexCoord);
    color += g_Texture3.Sample(g_SamplerState, In.TexCoord);
    color /= 4.0f;
    color.a = 1.0f;
    
    outDiffuse = color;
}