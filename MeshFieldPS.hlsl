#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //  ピクセルの法線を正規化
    float4 normal = normalize(In.Normal);
    
    //  ライト計算
    float light = -dot(dirDirection, normal.xyz);
    
    //  カメラからのベクトル
    float3 eyevec = In.WorldPosition.xyz - eyePos.xyz;
    eyevec = normalize(eyevec);
    
    
    
    //  反射ベクトル
    float3 refv = reflect(dirDirection.xyz, normal.xyz);
    refv = normalize(refv);  
    
    //  スペキュラー計算
    float specular = -dot(eyevec,refv);
    specular = saturate(specular);    
    specular = pow(specular, 30.0f);
    
    //  高さで色変える。
    float color_height_diff = In.WorldPosition.y / 5.0f;
   
    color_height_diff = pow(frac(color_height_diff), 4.0f);
    
    color_height_diff -= 1.0f - In.WorldPosition.y / 10.0f;
    color_height_diff = saturate(color_height_diff);

    //  中心からの距離を測る
    float dist = length(In.WorldPosition.xyz - eyePos);
    dist /= 70.0f;
    
    float rim = dot(eyevec, normal.xyz);        
    rim = 1.0f - abs(rim);
    rim = pow(rim, 10) * 2.0f;
    rim = saturate(rim);

//  Diffuse設定            
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
       
    outDiffuse.rgb *= light * dirColor;
    outDiffuse.a *= In.Diffuse.a;

    outDiffuse.rgb += specular;
    outDiffuse.b += color_height_diff - pow(dist, 4.0f);
       
    outDiffuse.b += rim;
    outDiffuse.rg -= saturate(0.5f - rim);
}