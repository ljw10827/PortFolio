// ���
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// �ؽ�ó
texture _texture00;
texture _texture01;
texture _texture02;
texture _texture03;
texture _splatTexture;

// ����
float4 _viewPosition;
float4 _lightDirection;

//! �Է� ����
struct STInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float3 tangent : TANGENT0;
	float3 binormal : BINORMAL0;
	float2 UV : TEXCOORD0;
};

// ! ��� ����
struct STOutput
{
	float4 position : POSITION0;
	float3 normal : TEXCOORD0;
	float3 tangent : TEXCOORD1;
	float3 binormal : TEXCOORD2;
	float2 UV : TEXCOORD3;
	float3 viewDirection : TEXCOORD4;
	float3 lightDirection : TEXCOORD5;
};

// ���� ���̴�
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;
	float4 worldPosition = mul(float4(input.position, 1.0), _worldMatrix);

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	float3 normal = mul(input.normal, (float3x3)_worldMatrix);
	output.normal = normalize(normal);

	float3 tangent = mul(input.tangent, (float3x3)_worldMatrix);
	output.tangent = normalize(tangent);

	float3 binormal = mul(input.binormal, (float3x3)_worldMatrix);
	output.binormal = normalize(binormal);

	float3 viewDirection = worldPosition.xyz - _viewPosition.xyz;
	output.viewDirection = normalize(viewDirection);

	float3 lightDirection = _lightDirection.xyz;
	output.lightDirection = normalize(lightDirection);

	output.UV = input.UV;

	return output;
}

// ���÷�
sampler2D _samplerA = sampler_state
{
	Texture = _texture00;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D _samplerB = sampler_state
{
	Texture = _texture01;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D _samplerC = sampler_state
{
	Texture = _texture02;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D _samplerD = sampler_state
{
	Texture = _texture03;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D _splatSampler = sampler_state
{
	Texture = _splatTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// �ȼ� ���̴�
float4 PSMain(STOutput input) : COLOR0
{
	float3 normal = normalize(input.normal);
	float3 tangent = normalize(input.tangent);
	float3 binormal = normalize(input.binormal);
	float3 lightDirection = normalize(input.lightDirection);
	float3 viewDirection = normalize(input.viewDirection);

	//float3 tangentNormal = tex2D(_normalSampler, input.UV).xyz;
	//tangentNormal = (tangentNormal * 2.0) - 1.0;

	///*
	//�븻 �� �ؽ�ó�� �ִ� �븻 ������ ���� ������ �������� �� �븻 �����̱� ������
	//�ش� ������ �ִ� �븻 ���͸� ���� �������� ��ȯ��Ű�� ���ؼ� ���������� �̷��
	//���������� ������� ����ؾ��Ѵ�.
	//*/
	//float3x3 inverseMatrix = float3x3(tangent, binormal, normal);

	//inverseMatrix = transpose(inverseMatrix);
	//normal = mul(tangentNormal, inverseMatrix);


	// ���ݻ縦 ����Ѵ�
	float diffuse = saturate(dot(-lightDirection, normal));

	float4 colorA = tex2D(_samplerA, input.UV);
	float4 colorB = tex2D(_samplerB, input.UV);
	float4 colorC = tex2D(_samplerC, input.UV);
	float4 colorD = tex2D(_samplerD, input.UV);

	float4 splatColor = tex2D(_splatSampler, input.UV);

	float blackColor = 1.0 - (splatColor.r + splatColor.g + splatColor.b);

	float4 diffuseColor = (colorA * splatColor.r) +
		(colorB * splatColor.g) +
		(colorC * splatColor.b) +
		(colorD * blackColor);

	float4 finalColor = diffuseColor;

	finalColor.rgb = finalColor.rgb * diffuse;
	finalColor.rgb = finalColor.rgb + (diffuseColor.rgb * 0.3);

	return finalColor;

}


// ��ũ��
technique MyTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}