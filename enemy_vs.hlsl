
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

      //  マトリックス
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    

    //  ノーマル
    float4 worldNormal, normal;
    normal = In.Normal;
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;

    //  頂点色を出力
    Out.Diffuse = In.Diffuse * Material.Diffuse;
    
    //  テクスチャ座標を出力
    Out.TexCoord = In.TexCoord;
    
    Out.tangent = normalize(mul(World, In.tangent));
    Out.biNormal = normalize(mul(World, In.biNormal));
    
    float4 depthPosition = mul(In.Position, World);
    depthPosition = mul(depthPosition, View);
    Out.depthInView = depthPosition.z;
    
}

