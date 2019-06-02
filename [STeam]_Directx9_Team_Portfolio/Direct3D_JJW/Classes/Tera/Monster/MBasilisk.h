#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CMonster.h"


class MBasilisk : public CMonster
{
public:

	enum class EPhase
	{
		PHASE00 = 0,
		PHASE01 = 1,
		PHASE02
	};

public:				// public �Լ�

	// ������ & �Ҹ���
	explicit MBasilisk(const std::string & monsterName);
	virtual ~MBasilisk(void);

	// �������̽�
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

public:
	// ������
	void Phase00(void);
	void Phase01(void);
	void Phase02(void);

	void NormalAtk();

	void BeAttacked(CPlayer * target, int damage);

public: 
	// ��ų
	//virtual void NormalAtk(void) override;

private:

	EPhase _phaseState;

	

};