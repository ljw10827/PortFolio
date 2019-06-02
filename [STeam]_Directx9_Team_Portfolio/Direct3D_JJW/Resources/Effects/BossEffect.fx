// �������
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// ����
float4 _viewPosition;
float4 _lightDirection;

// �ؽ�ó
texture _texture;
texture _normalTexture;

// ��Ÿ
int _numBlends;
float4x4 _boneMatrices[4];

// �Է� ����
struct STInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float3 tangent : TANGENT0;
	float3 binormal : BINORMAL0;
	float2 UV : TEXCOORD0;
	float4 boneWeight : BLENDWEIGHT0;
};

// ��� ����
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
	
	float leftBoneWeight = 1.0;

	/*
	_numblends = ���� ����ġ�� ����
	���밡��ġ�� ������ 0�� �϶�
	boneMatrix�� 0�̱⶧���� �������� �ȵ�(�������� �ȵǱ⶧���� ������ 1���� ��)
	���밡��ġ�� ���� ��� 1���� ���� ������ ���ǿ� ���������ʾ� �ٷ� ����������,
	�Ѱ��� boneMatrix�� 100% ����Ҽ��ְ� ���� �ϼ��� �� �ִ�.
	*/
	for (int i = 1; i < _numBlends; ++i) {
		float boneWeight = input.boneWeight[i];
		float4x4 boneMatrix = _boneMatrices[i];

		leftBoneWeight -= boneWeight;

		output.position += mul(float4(input.position, 1.0), boneMatrix) * boneWeight;
		output.normal += mul(input.normal, (float3x3)boneMatrix) * boneWeight;
		output.tangent += mul(input.tangent, (float3x3)boneMatrix) * boneWeight;
		output.binormal += mul(input.binormal, (float3x3)boneMatrix) * boneWeight;
	}

	output.position += mul(float4(input.position, 1.0), _boneMatrices[0]) * leftBoneWeight;
	output.normal += mul(input.normal, (float3x3)_boneMatrices[0]) * leftBoneWeight;
	output.tangent += mul(input.tangent, (float3x3)_boneMatrices[0]) * leftBoneWeight;
	output.binormal += mul(input.binormal, (float3x3)_boneMatrices[0]) * leftBoneWeight;

	// ����� ���� �̻��Ѱ����� �ٲ� w�� �������ش�.
	// ���������� ǥ���ϱ�����
	output.position.w = 1.0;
	float4 worldPosition = output.position;

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	output.normal = normalize(output.normal);
	output.tangent = normalize(output.tangent);
	output.binormal = normalize(output.binormal);

	float3 viewDirection = worldPosition.xyz - _viewPosition.xyz;
	output.viewDirection = normalize(viewDirection);

	float3 lightDirection = _lightDirection.xyz;
	output.lightDirection = normalize(lightDirection);

	output.UV = input.UV;

	return output;
}

// ���÷�
sampler2D _sampler = sampler_state
{
	Texture = _texture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// ���÷�
sampler2D _normalSampler = sampler_state
{
	Texture = _normalTexture;

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

	float3 tangentNormal = tex2D(_normalSampler, input.UV).xyz;
	tangentNormal = (tangentNormal * 2.0) - 1.0;

	float3x3 inverseMatrix = float3x3(tangent, binormal, normal);
	
	inverseMatrix = transpose(inverseMatrix);
	normal = mul(tangentNormal, inverseMatrix);

	// ���ݻ縦 ����Ѵ�
	float diffuse = saturate(dot(-lightDirection, normal));

	// ���ݻ縦 ����Ѵ�
	float specular = saturate(dot(reflect(lightDirection, normal), -viewDirection));
	specular = pow(specular, 500.0f);

	float4 finalColor = tex2D(_sampler, input.UV);

	float4 baseColor = finalColor;

	finalColor.rgb = finalColor.rgb * diffuse;
	finalColor.rgb = finalColor.rgb + (baseColor.rgb * specular);
	finalColor.rgb = finalColor.rgb + (baseColor.rgb * 0.3f);

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