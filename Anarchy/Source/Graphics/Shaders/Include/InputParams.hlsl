// Input for vertex and pixel shaders

struct VertexInput
{
	float3 position : POSITION0;
	float3 normal	: NORMAL0;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL0;
	float4 color : COLOR;
};