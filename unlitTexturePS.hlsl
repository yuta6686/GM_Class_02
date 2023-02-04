
#include "common.hlsl"


Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


void main(in PS_IN In, out float4 outDiffuse : SV_Target, out float depth : SV_Target1)
{
	
	//outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);	
	//outDiffuse *= In.Diffuse;

    float4 diff = g_Texture.Sample(g_SamplerState, In.TexCoord) * In.Diffuse;
    diff.rgb *= 1.2f;

    
    float Y = 0.299f * diff.x + 0.587f * diff.y + 0.114f * diff.b;
    float4 monochromeColor = float4(Y, Y, Y, diff.w);
   
    
    outDiffuse = lerp(diff, monochromeColor, monochoromRate);
    depth = In.depthInView;
}
