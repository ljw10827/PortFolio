#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

// ���� �޽�!

class CStaticMesh_Map : public CRenderObject
{
public:

	struct STParameters
	{
		std::string m_oMeshFileName;
		std::string m_oEffectFileName;
	};

public:

	// ������
	explicit CStaticMesh_Map(const STParameters& a_rParameters, bool AlphaIsTrue = false, const STSphereSRT _stSphere = { 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f) });

	// ��ü�� �׸��� ��
	virtual void preDrawObject(void) override;

	// ��ü �׸��� ��
	virtual void doDrawObject(void) override;

	// ��ü�� �׸� �� ó��
	virtual void postDrawObject(void) override;

	STSphereSRT getCDebugSTSphereSRT(void) { return cDebugSTR; }

private:
	STStaticMesh m_stStaticMesh;

private:
	// ����Ʈ�� �����غ���!
	LPD3DXEFFECT m_pEffect = nullptr;

	float m_fAlpha = 1.0f;

	bool IsbAlphaTrue;

	STSphereSRT cDebugSTR;
};