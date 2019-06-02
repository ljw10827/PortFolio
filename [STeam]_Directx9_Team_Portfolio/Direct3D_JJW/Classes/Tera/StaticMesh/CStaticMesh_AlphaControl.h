#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

// ���� �޽�!

class CStaticMesh_AlphaControl : public CRenderObject
{
public:

	struct STParameters
	{
		std::string m_oMeshFileName;
		std::string m_oEffectFileName;
	};

public:

	// ������
	explicit CStaticMesh_AlphaControl(const STParameters& a_rParameters, float Alpha);

	// ��ü�� �׸��� ��
	virtual void preDrawObject(void) override;

	// ��ü �׸��� ��
	virtual void doDrawObject(void) override;

	// ��ü�� �׸� �� ó��
	virtual void postDrawObject(void) override;

private:
	STStaticMesh m_stStaticMesh;

private:
	// ����Ʈ�� �����غ���!
	LPD3DXEFFECT m_pEffect = nullptr;

	float m_fAlpha = 0.0f;
};