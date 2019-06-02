// ���
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// ���� ����
float4 _lightDirection;
float4 _cameraPosition;

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
	float3 viewDirection : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float2 UV : TEXCOORD3;
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

	float3 viewDirection = worldPosition.xyz - _cameraPosition.xyz;
	output.viewDirection = normalize(viewDirection);

	output.lightDirection = normalize(_lightDirection.xyz);

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

/*
V = ���� ����
U = �븻 ����

V Dot U = ||V|| * ||U|| * cos0
*/

// �ȼ� ���̴�
float4 PSMain(STOutput input) : COLOR0
{
	float3 normal = normalize(input.normal);
	float3 lightDir = normalize(input.lightDirection);
	float3 viewDir = normalize(input.viewDirection);
	
	// ���ݻ縦 ����Ѵ�
	float diffuse = saturate(dot(-lightDir, normal));

	// ���ݻ縦 ����Ѵ�
	float specular = saturate(dot(reflect(lightDir, normal), -viewDir));
	specular = pow(specular, 20.0f);

	float4 finalColor = tex2D(_sampler, input.UV);
	finalColor.rgb = finalColor.rgb * diffuse;
	finalColor.rgb = finalColor.rgb + (float3(1.0f, 1.0f, 1.0f) * specular);

	return finalColor;
}

technique Example_19
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}