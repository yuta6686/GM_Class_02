
#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target, out float depth : SV_Target1)
{
    float4 color = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
    
    clip(t - 1.0f);

    outDiffuse = color; 
    depth = In.depthInView;
}