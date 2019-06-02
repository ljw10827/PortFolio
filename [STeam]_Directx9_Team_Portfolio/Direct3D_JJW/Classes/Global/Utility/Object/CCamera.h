#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CObject.h"

//! ī�޶�
class CCamera : public CObject
{
public:			// getter, setter

	//! �� ����� ��ȯ�Ѵ�
	D3DXMATRIXA16 getViewMatrix(void);

	//! ���� ����� ��ȯ�Ѵ�
	D3DXMATRIXA16 getProjectionMatrix(void);

	//! ��Ⱦ�� �����Ѵ�
	void setFieldOfView(const float a_fFieldOfView);

	//! �ֽ� ��ü�� �����Ѵ�
	void setFollowObject(CObject *a_pFollowObject, 
		const D3DXVECTOR3 &a_rstFollowOffset, 
		const EFollowType a_eFollowType = EFollowType::FREE);

	void setFollowObjectEnable(bool isEnable = true);

	bool getFollowObjectEnable() { return _isFollowEnable; }

	void setMapHeightPositionY(float HeightY) { mapHeightPositionY = HeightY; }

	void setMapHeightPositionYIsBool(bool HeightYTrue) { isBHeightPositionY = HeightYTrue; }

public:			// public �Լ�

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// ������

	//! ������
	explicit CCamera(const float a_fAspect, const float a_fFieldOfView);

private:			// private ����

	float m_fAspect = 0.0f;
	float m_fFieldOfView = 0.0f;
	EFollowType m_eFollowType = EFollowType::NONE;

	CObject *m_pFollowObject = nullptr;
	D3DXVECTOR3 m_stFollowOffset;

	D3DXMATRIXA16 m_stViewMatrix;
	D3DXMATRIXA16 m_stProjectionMatrix;

	bool _isFollowEnable = false;

	bool isBHeightPositionY = false;
	float mapHeightPositionY = 0.0f;

};
