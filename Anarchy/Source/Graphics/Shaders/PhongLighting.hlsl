// Phong lighting

#include "Include/InputParams.hlsl"
#include "Include/ConstantBuffer.hlsl"

PixelInput VertexMain(VertexInput input)
{
	PixelInput result;

	result.position = mul(float4(input.position, 1.0f), worldViewProjection);
	result.normal = input.normal;
	result.color = color;

	return result;
}

float4 PixelMain(PixelInput input) : SV_TARGET
{
	float4 finalColor;
	float luminance = saturate(dot(normalize(input.normal), normalize(lightDirection)));
	finalColor = saturate((input.color * luminance) + ambientLight);

	return finalColor;
}