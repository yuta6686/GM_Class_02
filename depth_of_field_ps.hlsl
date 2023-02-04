
#include "common.hlsl"


Texture2D g_bokeTexture : register(t0);
Texture2D g_depthTexture : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float depth = g_depthTexture.Sample(g_SamplerState, In.TexCoord);
    
    clip(depth - 200.0f);
    float4 boke = g_bokeTexture.Sample(g_SamplerState, In.TexCoord);
    
    boke.a = min(1.0f, (depth - 800.0f) / 500.0f);
    outDiffuse = boke;	
}
