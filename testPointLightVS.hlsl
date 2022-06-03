#include "common.hlsl"

///////////////////////////////////////////
// �֐��錾
///////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);

void main(in VS_IN In, out PS_IN Out)
{
    PS_IN psIn;
    psIn.Position = mul(World, In.Position);
    psIn.worldPos = psIn.Position;
    
    matrix vp;
    vp = mul(View, Projection);
    
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
	
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    
    
    
    //float light = -dot(ptLight.Direction.xyz, worldNormal.xyz);
    //light = saturate(light);
    
     // �f�B���N�V�������C�g�ɂ��Lambert�g�U���ˌ����v�Z����
    float3 diffDirection = CalcLambertDiffuse(ptLight.Direction.xyz, ptLight.ptColor.rgb, worldNormal.xyz);
    // �f�B���N�V�������C�g�ɂ��Phong���ʔ��ˌ����v�Z����
    float3 specDirection = CalcPhongSpecular(ptLight.Direction.xyz, ptLight.ptColor.rgb, psIn.worldPos,worldNormal.xyz);

    // �|�C���g���C�g�ɂ��Lambert�g�U���ˌ���Phong���ʔ��ˌ����v�Z����
    // step-7 �T�[�t�F�C�X�ɓ��˂���|�C���g���C�g�̌��̌������v�Z����
    float3 ligDir = psIn.worldPos - ptLight.ptPosition;
    ligDir = normalize(ligDir);

    // step-8 �����Ȃ���Lambert�g�U���ˌ����v�Z����
    float3 diffPoint = CalcLambertDiffuse(
        ligDir,
        ptLight.ptColor.rgb,
        worldNormal.xyz);

    // step-9 �����Ȃ���Phong���ʔ��ˌ����v�Z����
    float3 specPoint = CalcPhongSpecular(
        ligDir,
        ptLight.ptColor.rgb,
        psIn.worldPos,
        worldNormal.xyz
    );

    // step-10 �����ɂ��e�������v�Z����
    float3 distance = length(psIn.worldPos - ptLight.ptPosition);
    float affect = 1.0f - 1.0f / ptLight.ptRange * distance;
    
    affect = saturate(affect);
    
    affect = pow(affect, 10.0f);

    // step-11 �g�U���ˌ��Ƌ��ʔ��ˌ��ɉe��������Z���ĉe������߂�
    diffPoint *= affect;
    specPoint *= affect;

    // step-12 2�̔��ˌ������Z���čŏI�I�Ȕ��ˌ������߂�
    float diffuseLig = diffPoint + diffDirection;
    float specularLig = specPoint + specDirection;

    // �g�U���ˌ��Ƌ��ʔ��ˌ��𑫂��Z���āA�ŏI�I�Ȍ������߂�
    float3 lig = diffuseLig + specularLig + ptLight.Ambient;    
 
    
    Out.Diffuse = In.Diffuse * Material.Diffuse * ptLight.Diffuse;
    Out.Diffuse.xyz = Out.Diffuse.xyz * lig;
    Out.Diffuse += In.Diffuse * Material.Ambient * ptLight.Ambient;
    Out.Diffuse += Material.Emission;
    Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;


    Out.Position = mul(In.Position, wvp);
    
    Out.TexCoord = In.TexCoord;
}


/// <summary>
/// Lambert�g�U���ˌ����v�Z����
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // �s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
    float t = dot(normal, lightDirection) * -1.0f;

    // ���ς̒l��0�ȏ�̒l�ɂ���
    t = max(0.0f, t);

    // �g�U���ˌ����v�Z����
    return lightColor * t;
}

/// <summary>
/// Phong���ʔ��ˌ����v�Z����
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // ���˃x�N�g�������߂�
    float3 refVec = reflect(lightDirection, normal);

    // �������������T�[�t�F�C�X���王�_�ɐL�т�x�N�g�������߂�
    float3 toEye = ptLight.EyePos - worldPos;
    toEye = normalize(toEye);

    // ���ʔ��˂̋��������߂�
    float t = dot(refVec, toEye);

    // ���ʔ��˂̋�����0�ȏ�̐��l�ɂ���
    t = max(0.0f, t);

    // ���ʔ��˂̋������i��
    t = pow(t, 10.0f);

    // ���ʔ��ˌ������߂�
    return lightColor * t;
}