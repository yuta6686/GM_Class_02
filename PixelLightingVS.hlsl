#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    //  �}�g���b�N�X
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);    
    

    //  �m�[�}��
    float4 worldNormal, normal;
    normal = In.Normal;
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;

    //  ���_�F���o��
    Out.Diffuse = In.Diffuse;
    
    //  �e�N�X�`�����W���o��
    Out.TexCoord = In.TexCoord;
    Out.depthInView = In.Position.z;
}