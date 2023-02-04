
#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_Normal : register(t1);
Texture2D g_Env : register(t2);

SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target, out float depth : SV_Target1)
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
    float4 eyeVec = float4(In.WorldPosition.xyz - eyePos,0.0f);
    eyeVec = normalize(eyeVec);
    
    // ���}�b�s���O�v�Z
    float4 refVec = reflect(eyeVec, normal);
    refVec = normalize(refVec);
    refVec = (refVec + 1.0f) / 2.0f;
    
    float4 envTex = g_Env.SampleBias(g_SamplerState, refVec.xy, 0.0f);
    
    float4 baseTex = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    	//�����v�Z������
    float light = -dot(normal.xyz, dirDirection) * 2.0f;
    
        
        //�e�N�X�`���̃s�N�Z���F���擾
    outDiffuse = baseTex + envTex;
		

    outDiffuse.rgb *=
		In.Diffuse.rgb; //���邳�ƐF����Z
    
    outDiffuse.rgb /= 2.0f;
    outDiffuse.a *=
		In.Diffuse.a; //���ʌv�Z
    
    depth = In.depthInView;
}
