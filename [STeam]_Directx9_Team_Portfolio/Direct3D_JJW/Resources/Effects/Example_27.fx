// ���
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// ť��� �ؽ�ó
texture _cubeTexture;

// �Է� ����
struct STInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
};

// ��� ����
struct STOutput
{
	float4 position : POSITION0;
	float3 normal : TEXCOORD0;
};

// ���� ���̴�
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;

	float4 worldPosition = mul(float4(input.position, 1.0f), _worldMatrix);

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	float3 normal = mul(input.normal, (float3x3)_worldMatrix);
	output.normal = normalize(normal);

	return output;
}

samplerCUBE _cubeSampler = sampler_state
{
	Texture = _cubeTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// �ȼ� ���̴�
float4 PSMain(STOutput input) : COLOR0
{
	float3 normal = normalize(input.normal);
	return texCUBE(_cubeSampler, normal);
}

technique MyTechnique
{
	pass P0
	{
		CullMode = CW;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}