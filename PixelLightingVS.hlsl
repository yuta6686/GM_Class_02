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
    Out.Diffuse = In.Diffuse;
    
    //  テクスチャ座標を出力
    Out.TexCoord = In.TexCoord;
    Out.depthInView = In.Position.z;
}