
#include "common.hlsl"

///////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);

void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	//float light = -dot(Light.dirDirection.xyz, worldNormal.xyz);
	//light = saturate(light);
	
 //   float3 refVec = reflect(Light.dirDirection.xyz, In.Normal.xyz);
	
 //   float3 toEye = Light.eyePos - In.Position.xyz;
	
 //   light = dot(refVec, toEye);
 //   light = saturate(light);
	
 //   light = pow(light, 5.0f);
	
	 // ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(Light.dirDirection.xyz, Light.dirColor.xyz, In.Normal.xyz);
    // ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(Light.dirDirection.xyz, Light.dirColor.xyz, In.Position.xyz, In.Normal.xyz);
	
	 // ポイントライトによるLambert拡散反射光とPhong鏡面反射光を計算する
    // step-7 サーフェイスに入射するポイントライトの光の向きを計算する
    float3 ligDir = In.Position.xyz - Light.ptPosition;
    ligDir = normalize(ligDir);
	
	// step-8 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir,
        Light.ptColor,
        In.Normal.xyz);

    // step-9 減衰なしのPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
        ligDir,
        Light.ptColor,
        In.Position.xyz,
        In.Normal.xyz
    );
	
     // step-10 距離による影響率を計算する
    float3 distance = length(In.Position.xyz - Light.ptPosition);
    float affect = 1.0f - 1.0f / Light.ptRange * distance;
    
    affect = saturate(affect);
    
    affect = pow(affect, 3.0f);
    
      // step-11 拡散反射光と鏡面反射光に影響率を乗算して影響を弱める
    diffPoint *= affect;
    specPoint *= affect;

    // step-12 2つの反射光を合算して最終的な反射光を求める
    float diffuseLig = diffPoint + diffDirection;
    float specularLig = specPoint + specDirection;
    
    // 拡散反射光と鏡面反射光を足し算して、最終的な光を求める
    //float3 light = diffuseLig + specularLig + Light.ambientLight;    
    float3 light = diffPoint;

	Out.Diffuse.xyz = In.Diffuse.xyz * Material.Diffuse.xyz * light * Light.dirColor.xyz;
    Out.Diffuse.w = In.Diffuse.w * Material.Diffuse.w * Light.dirColor.w;
	
	//Out.Diffuse += In.Diffuse * Material.Ambient * Light.ambientLight;
    Out.Diffuse.xyz += In.Diffuse.xyz * Material.Ambient.xyz * Light.ambientLight;
    Out.Diffuse.w += In.Diffuse.w * Material.Ambient.a;
	
	Out.Diffuse += Material.Emission;
	Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;

	Out.Position = mul( In.Position, wvp );
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
    float3 toEye = Light.eyePos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 5.0f);

    // 鏡面反射光を求める
    return lightColor * t;
}