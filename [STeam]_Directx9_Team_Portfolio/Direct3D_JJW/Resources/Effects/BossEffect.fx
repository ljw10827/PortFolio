// 행렬정보
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// 조명
float4 _viewPosition;
float4 _lightDirection;

// 텍스처
texture _texture;
texture _normalTexture;

// 기타
int _numBlends;
float4x4 _boneMatrices[4];

// 입력 정보
struct STInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float3 tangent : TANGENT0;
	float3 binormal : BINORMAL0;
	float2 UV : TEXCOORD0;
	float4 boneWeight : BLENDWEIGHT0;
};

// 출력 정보
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

// 정점 쉐이더
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;
	
	float leftBoneWeight = 1.0;

	/*
	_numblends = 뼈대 가중치의 갯수
	뼈대가중치의 갯수가 0개 일때
	boneMatrix가 0이기때문에 곱해지면 안됨(곱해지면 안되기때문에 루프를 1부터 돔)
	뼈대가중치가 없을 경우 1부터 돌면 포문의 조건에 부합하지않아 바로 빠져나오며,
	한개의 boneMatrix를 100% 사용할수있게 식을 완성할 수 있다.
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

	// 계산을 통해 이상한값으로 바뀐 w를 보정해준다.
	// 동차공간을 표현하기위해
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

// 샘플러
sampler2D _sampler = sampler_state
{
	Texture = _texture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// 샘플러
sampler2D _normalSampler = sampler_state
{
	Texture = _normalTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};


// 픽셀 쉐이더
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

	// 난반사를 계산한다
	float diffuse = saturate(dot(-lightDirection, normal));

	// 정반사를 계산한다
	float specular = saturate(dot(reflect(lightDirection, normal), -viewDirection));
	specular = pow(specular, 500.0f);

	float4 finalColor = tex2D(_sampler, input.UV);

	float4 baseColor = finalColor;

	finalColor.rgb = finalColor.rgb * diffuse;
	finalColor.rgb = finalColor.rgb + (baseColor.rgb * specular);
	finalColor.rgb = finalColor.rgb + (baseColor.rgb * 0.3f);

	return finalColor;
}


// 테크닉
technique MyTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}