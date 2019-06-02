#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! 시간 관리자
class CTimeManager : public IUpdateable
{
public:
	// 자료형을 재정의한다.
	typedef std::chrono::system_clock::time_point TTimePoint;

public:			// 인터페이스 구현

	//! 상태를 갱신한다
	virtual void update(void) override;

public:			// getter

	//! 시간 간격을 반환한다
	float getDeltaTime(void);

	//! 구동 시간을 반환한다
	float getRunningTime(void);

public:			// public 함수

	//! 싱글턴
	DECLARE_SINGLETON(CTimeManager);

	//! 초기화
	void init(void);

	//! 시간 간격을 계산한다
	float calculateDeltaTime(const TTimePoint &a_rCurrentTimePoint,
		const TTimePoint &a_rPrevTimePoint);


private:		// private 변수

	float m_fDeltaTime = 0.0f;
	float m_fRunningTime = 0.0f;

	TTimePoint m_oPrevTimePoint;
	TTimePoint m_oStartTimePoint;
};