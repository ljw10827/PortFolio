// 행렬
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// 텍스처
texture _texture;

float _alpha;

// 광원 방향
float4 _lightDirection;
float4 _cameraPosition;

// 입력 정보
struct STInput
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float2 UV : TEXCOORD0;
};

// 출력 정보
struct STOutput
{
	float4 position : POSITION0;
	float3 normal : TEXCOORD0;
	float2 UV : TEXCOORD1;
	float3 viewDirection : TEXCOORD2;
	float3 lightDirection : TEXCOORD3;
};

// 정점 쉐이더
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;
	// 물체의 월드 좌표
	float4 worldPosition = mul(float4(input.position, 1.0), _worldMatrix);

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	float3 normal = mul(input.normal, (float3x3)_worldMatrix);
	output.normal = normalize(normal);

	float3 viewDirection = worldPosition.xyz - _cameraPosition.xyz;
	output.viewDirection = normalize(viewDirection);

	float3 lightDirection = _lightDirection.xyz;
	output.lightDirection = normalize(lightDirection);

	output.UV = input.UV;

	return output;
}

// 샘플러 설정
sampler2D _sampler = sampler_state
{
	Texture = _texture;

	AddressU = CLAMP;
	AddressV = CLAMP;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};



// 픽셀 쉐이더
float4 PSMain(STOutput input) : COLOR0
{
	float3 normal = normalize(input.normal);
	float3 lightDir = normalize(input.lightDirection);
	float3 viewDir = normalize(input.viewDirection);

	// 난반사를 계산한다
	float diffuse = saturate(dot(-lightDir, normal));

	// 정반사를 계산한다
	float specular = saturate(dot(reflect(lightDir, normal), -viewDir));
	specular = pow(specular, 30.0f);

	float4 finalColor = tex2D(_sampler, input.UV);
	//float4 baseColor = finalColor;

	//finalColor.rgb = finalColor.rgb * diffuse;
	//finalColor.rgb = finalColor.rgb + (baseColor.rgb * specular);
	//finalColor.rgb = finalColor.rgb + (baseColor.rgb * 0.5f);

	//finalColor.a = _alpha;

	return finalColor;
}

technique Example
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}