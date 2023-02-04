#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	
    matrix wvp;
    wvp = mul(World, View); // 1パス目はライトカメラの行列
    wvp = mul(wvp, Projection); // 2パス目は通常カメラの行列
    
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    
    float light = -dot(dirDirection, worldNormal.xyz);
    light = saturate(light);
    Out.Diffuse = In.Diffuse;
    Out.Diffuse.a = In.Diffuse.a;
    
    Out.Position = mul(In.Position, wvp);
    Out.Normal = worldNormal;
    
    
    float2 stealth;
    stealth.x = Out.Position.x / Out.Position.w;
    stealth.y = Out.Position.y / Out.Position.w;
    stealth.x = (stealth.x + 1.0f) / 2.0f;
    stealth.y = abs((stealth.y - 1.0f) / 2.0f);
    Out.TexCoord = stealth;
    
    //matrix lightwvp;
    //lightwvp = mul(World, Light.View);
    //lightwvp = mul(lightwvp, Light.Projecction);
    
    // Out.ShadowPosition = mul(In.Position, lightwvp);
    Out.depthInView = In.Position.z;


}