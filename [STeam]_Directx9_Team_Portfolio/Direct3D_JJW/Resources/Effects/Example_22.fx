// ���
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

//��Ÿ
float _alpha;

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

	output.UV = input.UV;

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
	
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// �ȼ� ���̴�
float4 PSMain(STOutput input) : COLOR0
{
	float4 finalColor = tex2D(_sampler, input.UV);

	//finalColor.a = _alpha;

	return finalColor;
}

technique Example_22
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}