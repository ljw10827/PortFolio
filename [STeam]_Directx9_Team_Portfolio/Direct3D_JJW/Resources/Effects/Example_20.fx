// ���
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// ��Ÿ
float _scaleX;
float _scaleY;

// �ؽ�ó
texture _texture;

// �Է� ����
struct STInput
{
	float3 position : POSITION0;
	float2 UV : TEXCOORD0;
};

// ��� ����
struct STOutput
{
	float4 position : POSITION0;
	float2 UV : TEXCOORD0;
};

// ���� ���̴�
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;
	// ��ü�� ���� ��ǥ
	float4 worldPosition = mul(float4(input.position, 1.0), _worldMatrix);

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	output.UV = float2(input.UV.x * _scaleX, input.UV.y * _scaleY);
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

	AddressU = WRAP;
	AddressV = WRAP;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

/*
V = ���� ����
U = �븻 ����

V Dot U = ||V|| * ||U|| * cos0
*/

// �ȼ� ���̴�
float4 PSMain(STOutput input) : COLOR0
{
	float4 finalColor = tex2D(_sampler, input.UV);

	float grayScale = (finalColor.r * 0.3) + (finalColor.g * 0.59) + (finalColor.b * 0.11);
	
	finalColor.rgb = float3(grayScale, grayScale, grayScale);
	return finalColor;
}

technique Example_20
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}