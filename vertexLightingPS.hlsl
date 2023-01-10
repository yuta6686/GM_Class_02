

#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 diff = g_Texture.Sample(g_SamplerState, In.TexCoord) * In.Diffuse;	
    
    float Y = 0.299f * diff.r + 0.587f * diff.g + 0.114f * diff.b;
    float4 monochromeColor = float4(Y, Y, Y,diff.a);
   
    
    outDiffuse = lerp(diff, monochromeColor,monochoromRate);    
}

