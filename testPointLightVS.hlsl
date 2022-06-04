#include "common.hlsl"

///////////////////////////////////////////
// 関数宣言
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
    
     // ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(dirDirection, dirColor, worldNormal.xyz);
    // ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(dirDirection,dirColor, psIn.worldPos,worldNormal.xyz);

    // ポイントライトによるLambert拡散反射光とPhong鏡面反射光を計算する
    // step-7 サーフェイスに入射するポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - ptPosition;
    ligDir = normalize(ligDir);

    // step-8 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir,
        ptColor,
        worldNormal.xyz);

    // step-9 減衰なしのPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
        ligDir,
        ptColor,
        psIn.worldPos,
        worldNormal.xyz
    );

    // step-10 距離による影響率を計算する
    float3 distance = length(psIn.worldPos - ptPosition);
    float affect = 1.0f - 1.0f / ptRange * distance;
    
    affect = saturate(affect);
    
    affect = pow(affect, 10.0f);

    // step-11 拡散反射光と鏡面反射光に影響率を乗算して影響を弱める
    diffPoint *= affect;
    specPoint *= affect;

    // step-12 2つの反射光を合算して最終的な反射光を求める
    float diffuseLig = diffPoint + diffDirection;
    float specularLig = specPoint + specDirection;

    // 拡散反射光と鏡面反射光を足し算して、最終的な光を求める
    float3 lig = diffuseLig + specularLig + ambientLight;    
 
    
    Out.Diffuse = In.Diffuse * Material.Diffuse;
    Out.Diffuse.xyz = Out.Diffuse.xyz * lig * dirColor;
    
    Out.Diffuse.xyz += In.Diffuse.xyz * Material.Ambient.xyz * ambientLight;
    Out.Diffuse.a += In.Diffuse.a * Material.Ambient.a;
    
    Out.Diffuse += Material.Emission;
    Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;


    Out.Position = mul(In.Position, wvp);
    
    Out.TexCoord = In.TexCoord;
}


/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}

/// <summary>
/// Phong鏡面反射光を計算する
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 10.0f);

    // 鏡面反射光を求める
    return lightColor * t;
}