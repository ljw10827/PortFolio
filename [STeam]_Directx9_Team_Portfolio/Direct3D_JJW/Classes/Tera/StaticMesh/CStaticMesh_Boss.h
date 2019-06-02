#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

// 정점 메시!

class CStaticMeshBoss : public CRenderObject
{
public:

	struct STParameters
	{
		std::string m_oMeshFileName;
		std::string m_oEffectFileName;
	};

public:

	// 생성자
	explicit CStaticMeshBoss(const STParameters& a_rParameters, bool AlphaIsTrue = false);

	// 객체를 그리기 전
	virtual void preDrawObject(void) override;

	// 객체 그리는 중
	virtual void doDrawObject(void) override;

	// 객체를 그린 후 처리
	virtual void postDrawObject(void) override;

private:

	STStaticMesh m_stStaticMesh;

private:
	// 이펙트로 생성해보기!
	LPD3DXEFFECT m_pEffect = nullptr;

	float m_fAlpha = 1.0f;
	bool IsbAlphaTrue = false;
};