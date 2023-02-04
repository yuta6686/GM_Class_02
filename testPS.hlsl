#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float2 random2(float2 st)
{
    st = float2(dot(st, float2(127.1f, 311.7f)),
    dot(st, float2(269.5f, 183.3f)));

    return -1.0f + 2.0f * frac(sin(st) * 43758.5f);
}

float perlinNoise(float2 st)
{
    float2 p = floor(st);
    float2 f = frac(st);
    float2 u = f * f * (3.0f - 2.0f * f);
    
    float v00 = random2(p + float2(0.0f, 0.0f));
    float v10 = random2(p + float2(1.0f, 0.0f));
    float v01 = random2(p + float2(0.0f, 1.0f));
    float v11 = random2(p + float2(1.0f, 1.0f));

    return lerp(lerp(dot(v00, f - float2(0.0f, 0.0f)), dot(v10, f - float2(1.0f, 0.0f)), u.x),
                lerp(dot(v01, f - float2(0.0f, 1.0f)), dot(v11, f - float2(1.0f, 1.0f)), u.x),
                u.y) + 0.5f;

}

void main(in PS_IN In, out float4 outDiffuse : SV_Target,out float depth : SV_Target1)
{
    float4 diffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    diffuse *= In.Diffuse;
    
    float2 uv = In.TexCoord * 8.0f;
    uv.x += pad1;
    uv.y += pad2;
    float c = (perlinNoise(uv) + perlinNoise(uv) * 0.125f);
    outDiffuse = float4(c, c, c, c) * diffuse;
    depth = In.depthInView;
}