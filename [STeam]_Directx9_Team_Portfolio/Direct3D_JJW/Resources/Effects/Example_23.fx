// ���
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// ���� ����
float4 _color;
float4 _lightDirection;
float4 _cameraPosition;

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
	float3 viewDirection : TEXCOORD1;
	float3 lightDirection : TEXCOORD2;
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

	float3 lightDirection = _lightDirection.xyz;
	output.lightDirection = normalize(lightDirection);

	return output;
}


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
	specular = pow(specular, 30.0f);

	float4 finalColor = _color;
	finalColor.rgb = finalColor.rgb * diffuse;
	finalColor.rgb = finalColor.rgb + (float3(1.0f, 1.0f, 1.0f) * specular);
	finalColor.rgb = finalColor.rgb + (_color.rgb * 0.3f);

	return finalColor;
}

technique Example_23
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}