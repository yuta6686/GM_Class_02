
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	float light = -dot(dirDirection, worldNormal.xyz);
	light = saturate(light);
	
    //float3 refVec = reflect(Light.Direction.xyz, In.Normal.xyz);
	
    //float3 toEye = Light.EyePos - In.Position.xyz;
	
    //light = dot(refVec, toEye);
    //light = saturate(light);
	
    //light = pow(light, 5.0f);
    Out.Diffuse = In.Diffuse * Material.Diffuse;
    Out.Diffuse.xyz = Out.Diffuse.xyz * light * dirColor;
    
    Out.Diffuse.xyz += In.Diffuse.xyz * Material.Ambient.xyz * ambientLight;
    Out.Diffuse.a += In.Diffuse.a * Material.Ambient.a;
	Out.Diffuse += Material.Emission;
	Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;
	


	Out.Position = mul( In.Position, wvp );
	Out.TexCoord = In.TexCoord;
	
    float4 depthPosition = mul(In.Position, World);
    depthPosition = mul(depthPosition, View);
    Out.depthInView = depthPosition.z;
}

