// 행렬
float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

// 1. 큐브맵
texture g_CubeTexture;

float4 g_Color;

// 2. 뷰의 위치
float4 g_stViewPosition;

/////////////여기까지 외부에서 오는 전역 변수////////////////////////

// 정점의 입력 정보
struct STInput
{
	float3 m_stPosition : POSITION0;
	float3 m_stNormal : NORMAL0;
};

// 정점의 출력 정보
struct STOutput
{
	float4 m_stPosition : POSITION0;
	float3 m_stNormal : TEXCOORD0;
	float3 m_stViewDirection : TEXCOORD1;
};

// 정점 쉐이더의 메인 함수

STOutput VSMain(STInput m_stInput)
{
	STOutput stOutput = (STOutput)0; // 일단 초기화

	float4 stWorldPosition = mul(float4(m_stInput.m_stPosition, 1.0f), g_stWorldMatrix);
	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	float3 stNormal = mul(m_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	// 카메라에서 물차가 들어오는 것
	float3 stViewDirection = stWorldPosition.xyz - g_stViewPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	return stOutput;
}

// 큐브용 셈플러를 사용한다.

samplerCUBE g_pCubeSampler = sampler_state
{
	Texture = g_CubeTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 PSMain(STOutput a_stInput) : COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);

	return texCUBE(g_pCubeSampler, stNormal);
}

technique MyTechnique
{
	pass P0
	{
		CullMode = CW;

		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}