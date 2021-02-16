// Empty Shader

#include "Include/InputParams.hlsl"
#include "Include/ConstantBuffer.hlsl"

PixelInput VertexMain(VertexInput input)
{
	PixelInput result;

	result.position = mul(float4(input.position, 1.0f), worldViewProjection);
	result.color = color;

	return result;
}

float4 PixelMain(PixelInput input) : SV_TARGET
{
	return input.color;
}