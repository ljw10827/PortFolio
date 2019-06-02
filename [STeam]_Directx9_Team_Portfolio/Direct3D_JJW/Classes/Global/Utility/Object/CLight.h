#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CObject.h"

//! ī�޶�
class CLight : public CObject
{
public:			// setter

	//! ���� Ȱ�� ���θ� �����Ѵ�
	void stLightEnable(const bool a_bIsLightEnable);

	//! ���ݻ� ������ �����Ѵ�
	void setDiffuseColor(const D3DXCOLOR &a_rstDiffuseColor);

	//! ���ݻ� ������ �����Ѵ�
	void setSpecularColor(const D3DXCOLOR &a_rSpecularColor);

public:			// public �Լ�

				//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// ������

				//! ������
	explicit CLight(const int a_nIndex);

private:			// private ����

	int m_nIndex = 0;
	bool m_bIsLightEnable = false;
	D3DLIGHT9 m_stLight;
};
