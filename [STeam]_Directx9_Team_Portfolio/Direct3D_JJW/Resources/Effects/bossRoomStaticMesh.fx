// ���
float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stPrijectionMatrix;

// �ؽ���
texture g_pTexture; // ����Ʈ�� �ٷ� �ؽ��ĸ� ���ð���

float4 g_stLightDirection;
float4 g_stViewPosition;

float g_fAlgha;

/////////////������� �ܺο��� ���� ���� ����////////////////////////


// ������ �Է� ����
struct STInput
{
	float3 m_stPosition : POSITION0;
	float3 m_stNormal : NORMAL0;
	float2 m_stUV : TEXCOORD0;
};

// ������ ��� ����
struct STOutput
{
	float4 m_stPosition : POSITION0;
	float2 m_stUV : TEXCOORD0;
	float3 m_stNormal : TEXCOORD1;
	float3 m_stViewDirection : TEXCOORD2; // TEXCOORD0�� �ε����̱� ������ ���ڸ� ���� ����Ѵ�.
	float3 m_stLightDirection : TEXCOORD3;
};

// ���� ���̴��� ���� �Լ�

STOutput VSMain(STInput m_stInput) // ���� ���� ������ ��ǥ�� ���� ��ǥ�̴�.
{
	STOutput stOutput = (STOutput)0;

	// g_stWorldMatrix�� 4x4 �ε� m_stPosition�� ���� ���� 3�� ���̶� �� ���� ���� ���̴�.
	float4 stWorldPosition = mul(float4(m_stInput.m_stPosition, 1.0f), g_stWorldMatrix);    // ���� ��ǥ�� �ٲ۴�.
	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);                           // �� ��ǥ�� �ٲ۴�.
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stPrijectionMatrix);               // ���� ��ǥ�� �ٲ۴�.

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

	// ��巹�� ��� ����
	addressU = WRAP;
	addressV = WRAP;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// �ȼ� ���̴��� ���� �Լ�
float4 PSMain(STOutput a_stInput) : COLOR0
{
	//float3 stNormal = normalize(a_stInput.m_stNormal);
	//float3 stLightDirection = normalize(a_stInput.m_stLightDirection);
	//float3 stViewDiretion = normalize(a_stInput.m_stViewDirection);

	//// ���ݻ�
	//float fDiffues = saturate(dot(-stLightDirection, stNormal));
	//
	//// ���ݻ�
	//float fSpecular = saturate(dot(reflect(stLightDirection, stNormal), -stViewDiretion));
	//fSpecular = pow(fSpecular, 20.0);

	//// ȯ�汤
	//float3 fambient = float3(0.1f, 0.1f, 0.1f);

	// ����� ����
	float4 stFinalColor = tex2D(g_pSampler, a_stInput.m_stUV); // �ʱ�ȭ! �� �ʿ��ϴ�!

	//stFinalColor.a = g_fAlgha;

	//return stFinalColor *0.7;
	return stFinalColor;

	//// ���ݻ� ����
	//stFinalColor.rgb = stFinalColor.rgb * fDiffues;

	//// ���ݻ� ����
	//stFinalColor.rgb = stFinalColor.rgb + (float3(1.0f, 1.0f, 1.0f)) * fSpecular;

	//// ȯ�汤 ����
	//stFinalColor.rgb += fambient;

	//return stFinalColor;

	return tex2D(g_pSampler, a_stInput.m_stUV);
}

// ������ �ϳ� �̻��� ��ũ���� �ʿ��ϴ�.

technique Example_24 // ��ũ�� �̸�
{
	// ���⿡�� �н��� ����
	pass P0 // ���⼭ ���� �ɼ� ����
	{
		//CullMode = NONE;
		VertexShader = compile vs_3_0 VSMain(); // �������̴��� ������ �ϰ� ���ñ��� ���ش�!
		PixelShader = compile ps_3_0 PSMain();  // �ȼ����̴��� ������ �ϰ� ���ñ��� ���ش�!
	}
}