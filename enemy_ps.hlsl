
#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_Normal : register(t1);
Texture2D g_Env : register(t2);

SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // �@��
    float4 normal;
    normal.x = -g_Normal.Sample(g_SamplerState, In.TexCoord).r;
    normal.y = g_Normal.Sample(g_SamplerState, In.TexCoord).b;
    normal.z = g_Normal.Sample(g_SamplerState, In.TexCoord).g;
    normal.w = 0.0f;
    normal = normal * 3.0f - 1.0f;
    normal = normalize(normal);
    
    // �����x�N�g��
    float4 eyeVec = float4(In.WorldPosition.xyz - eyePos, 0.0f);
    eyeVec = normalize(eyeVec);
    
    // ���}�b�s���O�v�Z
    float4 refVec = reflect(eyeVec, normal);
    refVec = normalize(refVec);
    refVec = (refVec + 1.0f) / 2.0f;
    
    float4 envTex = g_Env.SampleBias(g_SamplerState, refVec.xy, 0.0f);
    
    float4 baseTex = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    	//�����v�Z������
    float light = -dot(normal.xyz, dirDirection);
    
        
        //�e�N�X�`���̃s�N�Z���F���擾
    outDiffuse = baseTex + envTex;
    outDiffuse = pow(outDiffuse, 2.0f);
		

    outDiffuse.rgb *=
		In.Diffuse.rgb * 0.5f; //���邳�ƐF����Z
    outDiffuse.a *=
		In.Diffuse.a; //���ʌv�Z
}
