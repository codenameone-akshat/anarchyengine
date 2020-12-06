// Empty Shader

struct PSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer ConstantBuffer : register(b0)
{
	float4 mult;
}

PSInput VertexMain(float4 position : POSITION, 
					float4 color : COLOR)
{
	PSInput result;

	result.position = position;
	result.color = mult;

	return result;
}

float4 PixelMain(PSInput input) : SV_TARGET
{
	return input.color;
}