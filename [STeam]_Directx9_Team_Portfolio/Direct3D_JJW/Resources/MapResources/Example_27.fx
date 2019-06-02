// ���
float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

// 1. ť���
texture g_CubeTexture;

float4 g_Color;

// 2. ���� ��ġ
float4 g_stViewPosition;

/////////////������� �ܺο��� ���� ���� ����////////////////////////

// ������ �Է� ����
struct STInput
{
	float3 m_stPosition : POSITION0;
	float3 m_stNormal : NORMAL0;
};

// ������ ��� ����
struct STOutput
{
	float4 m_stPosition : POSITION0;
	float3 m_stNormal : TEXCOORD0;
	float3 m_stViewDirection : TEXCOORD1;
};

// ���� ���̴��� ���� �Լ�

STOutput VSMain(STInput m_stInput)
{
	STOutput stOutput = (STOutput)0; // �ϴ� �ʱ�ȭ

	float4 stWorldPosition = mul(float4(m_stInput.m_stPosition, 1.0f), g_stWorldMatrix);
	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	float3 stNormal = mul(m_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	// ī�޶󿡼� ������ ������ ��
	float3 stViewDirection = stWorldPosition.xyz - g_stViewPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	return stOutput;
}

// ť��� ���÷��� ����Ѵ�.

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