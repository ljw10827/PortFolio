// 행렬
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// 큐브맵 텍스처
texture _cubeMapTexture;

// 기타
float4 _viewPosition;

// 입력 정보
struct STInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
};

// 출력 정보
struct STOutput
{
	float4 position : POSITION0;
	float3 normal : TEXCOORD0;
	float3 viewDirection : TEXCOORD1;
};

// 정점 쉐이더
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;

	float4 worldPosition = mul(float4(input.position, 1.0f), _worldMatrix);

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	float3 normal = mul(input.normal, (float3x3)_worldMatrix);
	output.normal = normalize(normal);

	float3 viewDirection = worldPosition.xyz - _viewPosition.xyz;
	output.viewDirection = normalize(viewDirection);

	return output;
}

samplerCUBE _cubeSampler = sampler_state
{
	Texture = _cubeMapTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// 픽셀 쉐이더
float4 PSMain(STOutput input) : COLOR0
{
	float3 normal = normalize(input.normal);
	float3 viewDirection = normalize(input.viewDirection);

	float4 diffuseColor = texCUBE(_cubeSampler, reflect(viewDirection, normal));

	float4 finalColor = diffuseColor;

	finalColor.rgb = finalColor.rgb * 0.5f;
	finalColor.rgb = finalColor.rgb + (float3(0.8, 0.3, 0.3) * 0.3);

	return finalColor;
}

technique Example_26
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}