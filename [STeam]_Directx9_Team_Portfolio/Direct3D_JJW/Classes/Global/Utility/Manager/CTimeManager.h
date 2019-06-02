#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Interface/IUpdateable.h"

//! �ð� ������
class CTimeManager : public IUpdateable
{
public:
	// �ڷ����� �������Ѵ�.
	typedef std::chrono::system_clock::time_point TTimePoint;

public:			// �������̽� ����

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

public:			// getter

	//! �ð� ������ ��ȯ�Ѵ�
	float getDeltaTime(void);

	//! ���� �ð��� ��ȯ�Ѵ�
	float getRunningTime(void);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CTimeManager);

	//! �ʱ�ȭ
	void init(void);

	//! �ð� ������ ����Ѵ�
	float calculateDeltaTime(const TTimePoint &a_rCurrentTimePoint,
		const TTimePoint &a_rPrevTimePoint);


private:		// private ����

	float m_fDeltaTime = 0.0f;
	float m_fRunningTime = 0.0f;

	TTimePoint m_oPrevTimePoint;
	TTimePoint m_oStartTimePoint;
};