#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target, out float depth : SV_Target1)
{
    //  ピクセルの法線を正規化
    float4 normal = normalize(In.Normal);
    
    //  ライト計算
    float light = -dot(dirDirection, normal.xyz);
    
    //  カメラからのベクトル
    float3 eyevec = In.WorldPosition.xyz - eyePos.xyz;
    eyevec = normalize(eyevec);
    
    
    
    //  反射ベクトル
    //float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    //float3 i, n;
    //i = Light.Direction.xyz;
    //n = normal.xyz;
    //float3 refv = i - 2 * n * dot(i, n);
    //refv = normalize(refv);
    
    //  ハーフベクトル作成
    float3 halfv = dirDirection.xyz + eyevec;
    halfv = normalize(halfv);
    
    //  スペキュラー計算
    float specular = -dot(halfv, normal.xyz);
    specular = saturate(specular);
    
    specular = pow(specular, 30.0f) * 3.0f;

    float rim = 1.0f + dot(eyevec, normal.xyz) * 2.0f;
    
        
    rim = pow(rim, 2) * 2.0f;
    rim = saturate(rim);
    
//  Diffuse設定            
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
       
    outDiffuse.rgb *= light * dirColor;
    outDiffuse.a *= In.Diffuse.a;

    outDiffuse.rgb += specular;
    outDiffuse += rim;
    
    depth = In.depthInView;
    
    if (outDiffuse.a < 0.01)
        discard;

}