// 행렬
float4x4 _worldMatrix;
float4x4 _viewMatrix;
float4x4 _projectionMatrix;

texture _texture01;
texture _texture02;
texture _texture03;
texture _texture04;
texture _splatTexture;

float4 _lightDirection;
float4 _viewPosition;

struct STInput
{
	float3 m_stPosition : POSITION0;
	float3 m_stNormal : NORMAL0;
	float2 m_stUV : TEXCOORD0;
	float3 m_stTangent : TANGENT0;
	float3 m_stBinormal : BINORMAL0;
};

struct STOutput
{
	float4 m_stPosition : POSITION0;
	float3 m_stNormal : TEXCOORD0;
	float2 m_stUV : TEXCOORD1;
	float3 m_stTangent : TEXCOORD2;
	float3 m_stBinormal : TEXCOORD3;
	float3 m_stViewDirection : TEXCOORD4;
	float3 m_stLightDirection : TEXCOORD5;
};

STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	float4 stWorldPosition = mul(float4(a_stInput.m_stPosition, 1.0), _worldMatrix);

	stOutput.m_stPosition = mul(stWorldPosition, _viewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, _projectionMatrix);

	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)_worldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	stOutput.m_stUV = a_stInput.m_stUV;

	float3 stTangent = mul(a_stInput.m_stTangent, (float3x3)_worldMatrix);
	stOutput.m_stTangent = normalize(stTangent);

	float3 stBiNoraml = mul(a_stInput.m_stBinormal, (float3x3)_worldMatrix);
	stOutput.m_stBinormal = normalize(stBiNoraml);


	float3 stViewPosition = stWorldPosition.xyz - _viewPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewPosition);

	float3 stLightDirection = _lightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLightDirection);

	return stOutput;
}

sampler2D g_pSamplerA = sampler_state
{
	Texture = _texture01;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pSamplerB = sampler_state
{
	Texture = _texture02;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pSamplerC = sampler_state
{
	Texture = _texture03;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pSamplerD = sampler_state
{
	Texture = _texture04;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pSplatSampler = sampler_state
{
	Texture = _splatTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 PSMain(STOutput a_stInput) : COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);
	float3 stTangent = normalize(a_stInput.m_stTangent);
	float3 stBinormal = normalize(a_stInput.m_stBinormal);

	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);
	float3 stViewDiretion = normalize(a_stInput.m_stViewDirection);

	float4 stColorA = tex2D(g_pSamplerA, a_stInput.m_stUV);
	float4 stColorB = tex2D(g_pSamplerB, a_stInput.m_stUV);
	float4 stColorC = tex2D(g_pSamplerC, a_stInput.m_stUV);
	float4 stColorD = tex2D(g_pSamplerD, a_stInput.m_stUV);

	return stColorA;

	// 스플렛 컬러를 가지고 4가지 덱스쳐를 혼합한다.
	// A를 쓰면 투명도 들어가기에 못쓴다.
	// 그러므로 RGB로 블랙의 성분을 구한다.
	float4 stSplatColor = tex2D(g_pSplatSampler, a_stInput.m_stUV);

	float fBlackColor = 1.0 - (stSplatColor.r + stSplatColor.g + stSplatColor.b);

	// 밑의 연산에서 보듯이 예를 들어 스플랫 맵의 R 값이 커지면 텍스쳐A가 진해지고, G의 값이 작아지면 텍스쳐B는 연해지는 원리를 이용한 것이
	// 스플랫 맵이다.

	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	float fDiffues = saturate(dot(-stLightDirection, stNormal));

	float4 finalColor = (stColorA * stSplatColor.r) +
		(stColorB * stSplatColor.g) +
		(stColorC * stSplatColor.b) +
		(stColorD * fBlackColor);

	finalColor.rgb = finalColor.rgb * fDiffues;

	//환경광 넣기


	return finalColor;
}

technique MyTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}