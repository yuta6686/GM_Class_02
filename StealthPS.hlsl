#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureShadowDepth : register(t1);
Texture2D g_RenderingTexture : register(t2);

SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = g_RenderingTexture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse *= In.Diffuse;     
}
