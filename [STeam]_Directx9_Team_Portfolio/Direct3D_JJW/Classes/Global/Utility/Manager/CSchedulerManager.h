#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! 시간 관리자
class CSchedulerManager : public IUpdateable
{
public:			

	struct STScheduleData
	{
		float executeTime;
		std::function<void(void)> callback;
		bool isCompleteTime;
	};

public:			// 인터페이스 구현

	//! 상태를 갱신한다
	virtual void update(void) override;

public:			// getter

	void setScheduler(float executeTime, std::function<void(void)> callback);

	void RemoveScheule(void);

public:			// public 함수

	//! 싱글턴
	DECLARE_SINGLETON(CSchedulerManager);

	//! 초기화
	void init(void);


private:		// private 변수

	std::vector<STScheduleData> _scheduleList;
};