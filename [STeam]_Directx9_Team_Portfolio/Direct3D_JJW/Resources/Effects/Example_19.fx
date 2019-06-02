// 행렬
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// 광원 방향
float4 _lightDirection;
float4 _cameraPosition;

// 텍스처
texture _texture;

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
	float3 lightDirection : TEXCOORD0;
	float3 viewDirection : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float2 UV : TEXCOORD3;
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

	output.lightDirection = normalize(_lightDirection.xyz);

	output.UV = input.UV;
	return output;
}

/*
샘플러란?
:
텍스처로부터 UV좌표에 해당하는 정보를 추출하는 역할을 담당하는 객체.

이펙트 프레임워크 에서는 sampler_state 문법을 통해서
샘플러를 생성 및 설정 값을 지정해주는 것이 가능하다.

샘플러의 갯수는 텍스처의 갯수와 동일해야 한다.
(즉, 하나의 텍스처에는 하나의 샘플러가 필터링을 담당한다)
*/

// 샘플러 설정
sampler2D _sampler = sampler_state
{
	Texture = _texture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

/*
V = 광원 방향
U = 노말 방향

V Dot U = ||V|| * ||U|| * cos0
*/

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