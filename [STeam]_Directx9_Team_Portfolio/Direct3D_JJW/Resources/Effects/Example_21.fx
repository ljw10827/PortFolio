// ���
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

float4 _lightDirection;

//��Ÿ
float _offSetX;
float _offSetY;

// �ؽ�ó
texture _texture;

// �Է� ����
struct STInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float2 UV : TEXCOORD0;
};

// ��� ����
struct STOutput
{
	float4 position : POSITION0;
	float3 lightDirection : TEXCOORD0;
	float3 normal : TEXCOORD1;
	float2 UV : TEXCOORD2;
};

// ���� ���̴�
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;
	// ��ü�� ���� ��ǥ
	float4 worldPosition = mul(float4(input.position, 1.0), _worldMatrix);

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	float3 normal = mul(input.normal, (float3x3)_worldMatrix);
	output.normal = normalize(normal);

	output.UV = input.UV + float2(_offSetX, _offSetY);
	output.lightDirection = normalize(_lightDirection.xyz);

	return output;
}

/*
���÷���?
:
�ؽ�ó�κ��� UV��ǥ�� �ش��ϴ� ������ �����ϴ� ������ ����ϴ� ��ü.

����Ʈ �����ӿ�ũ ������ sampler_state ������ ���ؼ�
���÷��� ���� �� ���� ���� �������ִ� ���� �����ϴ�.

���÷��� ������ �ؽ�ó�� ������ �����ؾ� �Ѵ�.
(��, �ϳ��� �ؽ�ó���� �ϳ��� ���÷��� ���͸��� ����Ѵ�)
*/

// ���÷� ����
sampler2D _sampler = sampler_state
{
	Texture = _texture;
	
	AddressU = CLAMP;
	AddressV = CLAMP;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// �ȼ� ���̴�
float4 PSMain(STOutput input) : COLOR0
{
	float3 normal = normalize(input.normal);
	float3 lightDir = normalize(input.lightDirection);

	// ���ݻ縦 ����Ѵ�
	float diffuse = saturate(dot(-lightDir, normal));
	diffuse = ceil(diffuse * 3) / 3.0f;

	float4 finalColor = tex2D(_sampler, input.UV);
	finalColor.rgb = finalColor.rgb * diffuse;

	return finalColor;
}

technique Example_21
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}