#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_NormalTexture : register(t1);
Texture2D g_PixelNoiseTexture : register(t2);
Texture2D g_Texture2 : register(t3);
SamplerState g_SamplerState : register(s0);

// �萔
static const float PI = 3.1415926f;

// �֐�
float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    float3 binSpaceNormal = g_NormalTexture.SampleLevel(g_SamplerState, uv, 0.0f).xyz;
    binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;
    float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;
    return newNormal;
}

// �x�b�N�}�����z���v�Z����
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
    return D;
}

// �t���l�����v�Z�BSchlick�ߎ����g�p
float SpcFresnel(float f0, float u)
{
    return f0 + (1 - f0) * pow(1 - u, 5);
}

// Cook-Torrance���f���̋��ʔ��˂��v�Z
float CookTorranceSpecular(float3 L, float3 V, float3 N, float metallic)
{
    float microfacet = 0.76f;
    
    // �����x�𐂒����˂̂Ƃ��̃t���l�����˗��Ƃ��Ĉ���
    // �����x�������قǃt���l�����˂͑傫���Ȃ�
    float f0 = metallic;
    
    /// ���C�g�Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g��
    float3 H = normalize(L + V);
    
    // �e��x�N�g�����ǂꂭ�炢���Ă��邩����ς𗘗p���ċ��߂�
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));
    float NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));

    // D�����x�b�N�}�����z��p���Čv�Z����
    float D = Beckmann(microfacet, NdotH);
    
    float F = SpcFresnel(f0, VdotH);
    
    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));
    
    float m = PI * NdotV * NdotH;
    
    return max(F * D * G / m, 0.0f);        
}


// N : �m�[�}��
// L : �����Ɍ������x�N�g�� direction?
// V : �����Ɍ������x�N�g�� eyevec
float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V)
{
    float dotNL = saturate(dot(N, L));
    
    float dotNV = saturate(dot(N, V));
    
    return (dotNL * dotNV);

}

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //  �s�N�Z���̖@���𐳋K��
    float3 normal = GetNormal(In.Normal.xyz, In.tangent, In.biNormal, In.TexCoord);
    //normal.x = -g_NormalTexture.Sample(g_SamplerState, In.TexCoord).r;
    //normal.y = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).b;
    //normal.z = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).g;
    
    normal = normal * 2.0f - 0.5f;
    normal = normalize(normal);
    
    float3 localNormal = g_NormalTexture.Sample(g_SamplerState, In.TexCoord).xyz;
    localNormal = (localNormal - 0.5f) * 2.0f;
    
    normal = In.tangent * localNormal.x + In.biNormal * localNormal.y + normal * localNormal.z;
    
    //float4 ratio = g_PixelNoiseTexture.Sample(g_SamplerState, In.TexCoord);
    //float4 diffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    //float4 diffuse2 = g_Texture2.Sample(g_SamplerState, In.TexCoord);
    //float4 resultDiffuse = lerp(diffuse, diffuse2, ratio.r);
    
    float4 albedoColor = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    float3 specColor = albedoColor;
    
    float metalic = 0.5f;
    
    float smooth = 0.5f;
    
    float toEye = normalize(eyePos.xyz - In.WorldPosition.xyz);
    float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -dirDirection, toEye);
    
    // ���K��Lambert�g�U����
    float NdotL = saturate(dot(normal, -dirDirection));
    float3 lambertDiffuse = dirDirection * NdotL / PI;
    
    // �ŏI�I�Ȋg�U���ˌ����v�Z����
    float3 diffuse = albedoColor.rgb * diffuseFromFresnel * lambertDiffuse;
    
    // Cook-Torrance���f���𗘗p�������ʔ��˗����v�Z����
    float3 spec = CookTorranceSpecular(
    -dirDirection, toEye, normal, smooth) * dirColor;
    
    spec *= lerp(float3(1.0, 1.0f, 1.0f), specColor, metalic);
    
    
    //  ���C�g�v�Z
    float light = saturate(dot(In.Normal.xyz, -dirDirection)) / PI + diffuseFromFresnel;
    
    //  �J��������̃x�N�g��
    float3 eyevec = In.WorldPosition.xyz - eyePos.xyz;
    eyevec = normalize(eyevec);
    
    
    

//  Diffuse�ݒ�            
    outDiffuse.rgb = diffuse * (1.0f - smooth) + spec;
    
    
    //outDiffuse.rgb *= light;
    outDiffuse.a = In.Diffuse.a;


    outDiffuse.rgb += ambientLight * 1.2f * albedoColor;
    
}