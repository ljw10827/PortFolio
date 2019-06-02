#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! �ð� ������
class CSchedulerManager : public IUpdateable
{
public:			

	struct STScheduleData
	{
		float executeTime;
		std::function<void(void)> callback;
		bool isCompleteTime;
	};

public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter

	void setScheduler(float executeTime, std::function<void(void)> callback);

	void RemoveScheule(void);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CSchedulerManager);

	//! �ʱ�ȭ
	void init(void);


private:		// private ����

	std::vector<STScheduleData> _scheduleList;
};