#include "common.hlsl"
Texture2D g_Texture : register(t0);
void main(in VS_IN In, out PS_BlurIN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.pos = mul(In.Position, wvp);
    
    float2 texSize;
    float level;
    
    g_Texture.GetDimensions(0, texSize.x, texSize.y, level);
    
    float2 tex = In.TexCoord;
    
    Out.tex0.xy = float2(1.0f / texSize.x, 0.0f);
    Out.tex1.xy = float2(3.0f / texSize.x, 0.0f);
    Out.tex2.xy = float2(5.0f / texSize.x, 0.0f);
    Out.tex3.xy = float2(7.0f / texSize.x, 0.0f);
    Out.tex4.xy = float2(9.0f / texSize.x, 0.0f);
    Out.tex5.xy = float2(11.0f / texSize.x, 0.0);
    Out.tex6.xy = float2(13.0f / texSize.x, 0.0f);
    Out.tex7.xy = float2(15.0f / texSize.x, 0.0f);

    Out.tex0.zw = Out.tex0.xy * -1.0f;
    Out.tex1.zw = Out.tex1.xy * -1.0f;
    Out.tex2.zw = Out.tex2.xy * -1.0f;
    Out.tex3.zw = Out.tex3.xy * -1.0f;
    Out.tex4.zw = Out.tex4.xy * -1.0f;
    Out.tex5.zw = Out.tex5.xy * -1.0f;
    Out.tex6.zw = Out.tex6.xy * -1.0f;
    Out.tex7.zw = Out.tex7.xy * -1.0f;
    
    Out.tex0 += float4(tex, tex);
    Out.tex1 += float4(tex, tex);
    Out.tex2 += float4(tex, tex);
    Out.tex3 += float4(tex, tex);
    Out.tex4 += float4(tex, tex);
    Out.tex5 += float4(tex, tex);
    Out.tex6 += float4(tex, tex);
    Out.tex7 += float4(tex, tex);
}