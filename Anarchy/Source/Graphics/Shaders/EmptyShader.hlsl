// Empty Shader

struct PSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer ConstantBuffer : register(b0)
{
	float4 col;
	float4x4 wvp;
}

PSInput VertexMain(float3 position : POSITION)
{
	PSInput result;

	result.position = mul(float4(position, 1.0f), wvp);
	result.color = col;

	return result;
}

float4 PixelMain(PSInput input) : SV_TARGET
{
	return input.color;
}