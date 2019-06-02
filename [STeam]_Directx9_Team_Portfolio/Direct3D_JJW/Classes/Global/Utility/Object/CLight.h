#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CObject.h"

//! 카메라
class CLight : public CObject
{
public:			// setter

	//! 광원 활성 여부를 변경한다
	void stLightEnable(const bool a_bIsLightEnable);

	//! 난반사 색상을 변경한다
	void setDiffuseColor(const D3DXCOLOR &a_rstDiffuseColor);

	//! 정반사 색상을 변경한다
	void setSpecularColor(const D3DXCOLOR &a_rSpecularColor);

public:			// public 함수

				//! 상태를 갱신한다
	virtual void update(void) override;

public:			// 생성자

				//! 생성자
	explicit CLight(const int a_nIndex);

private:			// private 변수

	int m_nIndex = 0;
	bool m_bIsLightEnable = false;
	D3DLIGHT9 m_stLight;
};
