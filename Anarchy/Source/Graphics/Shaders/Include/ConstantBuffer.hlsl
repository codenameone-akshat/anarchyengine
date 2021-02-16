// Constant Buffer 

cbuffer ConstantBuffer : register(b0)
{
	float4 color;
	float4x4 worldViewProjection;
	float4 ambientLight;
	float3 lightDirection;
	
	float pad0;
}