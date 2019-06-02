// 행렬
float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stPrijectionMatrix;

// 텍스쳐
texture g_pTexture; // 이펙트에 바로 텍스쳐를 셋팅가능

float4 g_stLightDirection;
float4 g_stViewPosition;

float g_fAlgha;

/////////////여기까지 외부에서 오는 전역 변수////////////////////////


// 정점의 입력 정보
struct STInput
{
	float3 m_stPosition : POSITION0;
	float3 m_stNormal : NORMAL0;
	float2 m_stUV : TEXCOORD0;
};

// 정점의 출력 정보
struct STOutput
{
	float4 m_stPosition : POSITION0;
	float2 m_stUV : TEXCOORD0;
	float3 m_stNormal : TEXCOORD1;
	float3 m_stViewDirection : TEXCOORD2; // TEXCOORD0는 인덱스이기 때문에 숫자를 따로 줘야한다.
	float3 m_stLightDirection : TEXCOORD3;
};

// 정점 쉐이더의 메인 함수

STOutput VSMain(STInput m_stInput) // 지금 들어온 정점의 좌표는 로컬 좌표이다.
{
	STOutput stOutput = (STOutput)0;

	// g_stWorldMatrix는 4x4 인데 m_stPosition는 인자 값이 3개 뿐이라서 한 차원 높인 것이다.
	float4 stWorldPosition = mul(float4(m_stInput.m_stPosition, 1.0f), g_stWorldMatrix);    // 월드 좌표로 바꾼다.
	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);                           // 뷰 좌표로 바꾼다.
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stPrijectionMatrix);               // 투영 좌표로 바꾼다.

	stOutput.m_stUV = m_stInput.m_stUV;

	float3 stNormal = mul(m_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	float3 stViewPosition = stWorldPosition.xyz - g_stViewPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewPosition);

	float3 stLight = g_stLightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLight);
	//stOutput.m_stLightDirection = normalize(g_stLightDirection.xyz);

	return stOutput;
}

sampler2D g_pSampler = sampler_state
{
	Texture = g_pTexture;

	// 어드레스 모드 설정
	addressU = WRAP;
	addressV = WRAP;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// 픽셀 쉐이더의 메인 함수
float4 PSMain(STOutput a_stInput) : COLOR0
{
	//float3 stNormal = normalize(a_stInput.m_stNormal);
	//float3 stLightDirection = normalize(a_stInput.m_stLightDirection);
	//float3 stViewDiretion = normalize(a_stInput.m_stViewDirection);

	//// 난반사
	//float fDiffues = saturate(dot(-stLightDirection, stNormal));
	//
	//// 정반사
	//float fSpecular = saturate(dot(reflect(stLightDirection, stNormal), -stViewDiretion));
	//fSpecular = pow(fSpecular, 20.0);

	//// 환경광
	//float3 fambient = float3(0.1f, 0.1f, 0.1f);

	// 출력할 변수
	float4 stFinalColor = tex2D(g_pSampler, a_stInput.m_stUV); // 초기화! 꼭 필요하다!

	//stFinalColor.a = g_fAlgha;

	//return stFinalColor *0.7;
	return stFinalColor;

	//// 난반사 도입
	//stFinalColor.rgb = stFinalColor.rgb * fDiffues;

	//// 정반사 도입
	//stFinalColor.rgb = stFinalColor.rgb + (float3(1.0f, 1.0f, 1.0f)) * fSpecular;

	//// 환경광 도입
	//stFinalColor.rgb += fambient;

	//return stFinalColor;

	return tex2D(g_pSampler, a_stInput.m_stUV);
}

// 무조건 하나 이상의 테크닉이 필요하다.

technique Example_24 // 테크닉 이름
{
	// 여기에는 패스를 지정
	pass P0 // 여기서 랜더 옵션 설정
	{
		//CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain(); // 정점쉐이더를 컴파일 하고 셋팅까지 해준다!
		PixelShader = compile ps_3_0 PSMain();  // 픽셀쉐이더를 컴파일 하고 셋팅까지 해준다!
	}
}