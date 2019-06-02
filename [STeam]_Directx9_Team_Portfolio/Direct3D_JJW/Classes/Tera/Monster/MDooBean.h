#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CMonster.h"


class MDooBean : public CMonster
{
public:				// public 함수

	// 생성자 & 소멸자
	explicit MDooBean(const std::string & monsterName);
	virtual ~MDooBean(void);

	// 인터페이스
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

	virtual void NormalAtk(void) override;
	void BeAttacked(CPlayer * target, int damage);
};