#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //  �s�N�Z���̖@���𐳋K��
    float4 normal = normalize(In.Normal);
    
    //  ���C�g�v�Z
    float light = -dot(dirDirection, normal.xyz);
    
    //  �J��������̃x�N�g��
    float3 eyevec = In.WorldPosition.xyz - eyePos.xyz;
    eyevec = normalize(eyevec);
    
    
    
    //  ���˃x�N�g��
    float3 refv = reflect(dirDirection.xyz, normal.xyz);
    refv = normalize(refv);  
    
    //  �X�y�L�����[�v�Z
    float specular = -dot(eyevec,refv);
    specular = saturate(specular);    
    specular = pow(specular, 30.0f);
    
    //  �����ŐF�ς���B
    float color_height_diff = In.WorldPosition.y / 5.0f;
   
    color_height_diff = pow(frac(color_height_diff), 4.0f);
    
    color_height_diff -= 1.0f - In.WorldPosition.y / 10.0f;
    color_height_diff = saturate(color_height_diff);

    //  ���S����̋����𑪂�
    float dist = length(In.WorldPosition.xyz - eyePos);
    dist /= 70.0f;
    
    float rim = dot(eyevec, normal.xyz);        
    rim = 1.0f - abs(rim);
    rim = pow(rim, 10) * 2.0f;
    rim = saturate(rim);

//  Diffuse�ݒ�            
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
       
    outDiffuse.rgb *= light * dirColor;
    outDiffuse.a *= In.Diffuse.a;

    outDiffuse.rgb += specular;
    outDiffuse.b += color_height_diff - pow(dist, 4.0f);
       
    outDiffuse.b += rim;
    outDiffuse.rg -= saturate(0.5f - rim);
}