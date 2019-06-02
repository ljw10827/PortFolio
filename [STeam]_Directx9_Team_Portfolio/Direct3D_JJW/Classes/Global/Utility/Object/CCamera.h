#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CObject.h"

//! 카메라
class CCamera : public CObject
{
public:			// getter, setter

	//! 뷰 행렬을 반환한다
	D3DXMATRIXA16 getViewMatrix(void);

	//! 투영 행렬을 반환한다
	D3DXMATRIXA16 getProjectionMatrix(void);

	//! 종횡비를 변경한다
	void setFieldOfView(const float a_fFieldOfView);

	//! 주시 객체를 변경한다
	void setFollowObject(CObject *a_pFollowObject, 
		const D3DXVECTOR3 &a_rstFollowOffset, 
		const EFollowType a_eFollowType = EFollowType::FREE);

	void setFollowObjectEnable(bool isEnable = true);

	bool getFollowObjectEnable() { return _isFollowEnable; }

	void setMapHeightPositionY(float HeightY) { mapHeightPositionY = HeightY; }

	void setMapHeightPositionYIsBool(bool HeightYTrue) { isBHeightPositionY = HeightYTrue; }

public:			// public 함수

	//! 상태를 갱신한다
	virtual void update(void) override;

public:			// 생성자

	//! 생성자
	explicit CCamera(const float a_fAspect, const float a_fFieldOfView);

private:			// private 변수

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
