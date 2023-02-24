
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
    
    float4 depthPosition = mul(In.Position, World);
    depthPosition = mul(depthPosition, View);
    Out.depthInView = depthPosition.z;
}

