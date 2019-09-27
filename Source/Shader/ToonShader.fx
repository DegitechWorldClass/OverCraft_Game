struct VS_INPUT
{
	float4 mPosition : POSITION;
	float3 mNormal: NORMAL;
};

struct VS_OUTPUT
{
	float4 mPosition : POSITION;
	float3 mDiffuse : TEXCOORD1;
};

float4x4 gWorldViewProjectionMatrix;
float4x4 gInvWorldMatrix;

float4 gWorldLightPosition;

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	
	Output.mPosition = mul(Input.mPosition, gWorldViewProjectionMatrix);
	
	float3 objectLightPosition = mul(gWorldLightPosition, gInvWorldMatrix);
	float3 lightDir = normalize(Input.mPosition.xyz - objectLightPosition);

	Output.mDiffuse = dot(-lightDir, normalize(Input.mNormal));

	return(Output);

}