// 행렬
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

// 기타
float _scaleX;
float _scaleY;

// 텍스처
texture _texture;

// 입력 정보
struct STInput
{
	float3 position : POSITION0;
	float2 UV : TEXCOORD0;
};

// 출력 정보
struct STOutput
{
	float4 position : POSITION0;
	float2 UV : TEXCOORD0;
};

// 정점 쉐이더
STOutput VSMain(STInput input)
{
	STOutput output = (STOutput)0;
	// 물체의 월드 좌표
	float4 worldPosition = mul(float4(input.position, 1.0), _worldMatrix);

	output.position = mul(worldPosition, _viewMatrix);
	output.position = mul(output.position, _projectionMatrix);

	output.UV = float2(input.UV.x * _scaleX, input.UV.y * _scaleY);
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

	AddressU = WRAP;
	AddressV = WRAP;

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