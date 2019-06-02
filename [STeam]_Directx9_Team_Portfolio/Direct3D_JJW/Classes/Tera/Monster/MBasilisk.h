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

public:				// public 함수

	// 생성자 & 소멸자
	explicit MBasilisk(const std::string & monsterName);
	virtual ~MBasilisk(void);

	// 인터페이스
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

public:
	// 페이즈
	void Phase00(void);
	void Phase01(void);
	void Phase02(void);

	void NormalAtk();

	void BeAttacked(CPlayer * target, int damage);

public: 
	// 스킬
	//virtual void NormalAtk(void) override;

private:

	EPhase _phaseState;

	

};