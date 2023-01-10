#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureGrad : register(t1);
Texture2D g_TextureGradColor : register(t2);
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

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 diffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    float4 gradation = g_TextureGrad.Sample(g_SamplerState, In.TexCoord);
    
    diffuse *= In.Diffuse;
    
    float2 uv = In.TexCoord * 16.0f;
    uv.x += pad1;
    uv.y += pad2;
    // float Y = GetMonochrome(gradation.rgb);
    
    float c = (perlinNoise(uv) + perlinNoise(uv) * 0.125f);
    
    float dist = length(In.WorldPosition.xyz);
    dist /= 20.0f;   
    
    dist = pow(dist, 2.0f);
        
    float4 result;
    result.r = c;
    result.g = c;
    result.b = c;
    result.a = c;
    
    
    //result.a *= Y;
    
    float4 color = g_TextureGradColor.Sample(g_SamplerState, float2((dist - 0.4f) / 2.0f, 0.0f));
    
    outDiffuse.r = dist * result ;
    outDiffuse.g = dist * result ;
    outDiffuse.b = dist * result ;
    outDiffuse.a = dist * result ;
    
    if (outDiffuse.r > 0.1f && outDiffuse.r < 0.9f)
    {
        outDiffuse.rgba *= color;
    }
    else
    {
        outDiffuse.a = 0.0f;
    }
        
                          
    if (outDiffuse.r > 4.0f)      
    {
        dist = 0.0f;
    }

    outDiffuse *= dist;
}