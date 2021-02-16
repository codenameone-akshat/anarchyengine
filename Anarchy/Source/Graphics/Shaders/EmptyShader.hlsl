// Empty Shader

#include "Include/InputParams.hlsl"
#include "Include/ConstantBuffer.hlsl"


PixelInput VertexMain(float3 position : POSITION)
{
	PixelInput result;

	result.position = mul(float4(position, 1.0f), worldViewProjection);
	result.color = color;

	return result;
}

float4 PixelMain(PixelInput input) : SV_TARGET
{
	return input.color;
}