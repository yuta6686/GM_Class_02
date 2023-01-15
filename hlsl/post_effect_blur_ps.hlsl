#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_BlurIN In, out float4 outDiffuse : SV_Target0)
{
    outDiffuse = weight[0].x * g_Texture.Sample(g_SamplerState, In.tex0.xy);
    outDiffuse += weight[0].y * g_Texture.Sample(g_SamplerState, In.tex1.xy);
    outDiffuse += weight[0].z * g_Texture.Sample(g_SamplerState, In.tex2.xy);
    outDiffuse += weight[0].w * g_Texture.Sample(g_SamplerState, In.tex3.xy);
    outDiffuse += weight[1].x * g_Texture.Sample(g_SamplerState, In.tex4.xy);
    outDiffuse += weight[1].y * g_Texture.Sample(g_SamplerState, In.tex5.xy);
    outDiffuse += weight[1].z * g_Texture.Sample(g_SamplerState, In.tex6.xy);
    outDiffuse += weight[1].w * g_Texture.Sample(g_SamplerState, In.tex7.xy);
    
    outDiffuse += weight[0].x * g_Texture.Sample(g_SamplerState, In.tex0.zw);
    outDiffuse += weight[0].y * g_Texture.Sample(g_SamplerState, In.tex1.zw);
    outDiffuse += weight[0].z * g_Texture.Sample(g_SamplerState, In.tex2.zw);
    outDiffuse += weight[0].w * g_Texture.Sample(g_SamplerState, In.tex3.zw);
    outDiffuse += weight[1].x * g_Texture.Sample(g_SamplerState, In.tex4.zw);
    outDiffuse += weight[1].y * g_Texture.Sample(g_SamplerState, In.tex5.zw);
    outDiffuse += weight[1].z * g_Texture.Sample(g_SamplerState, In.tex6.zw);
    outDiffuse += weight[1].w * g_Texture.Sample(g_SamplerState, In.tex7.zw);
    
   // outDiffuse = g_Texture.Sample(g_SamplerState, In.tex0.xy);
   
}