#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CMonster.h"


class MDooBean : public CMonster
{
public:				// public �Լ�

	// ������ & �Ҹ���
	explicit MDooBean(const std::string & monsterName);
	virtual ~MDooBean(void);

	// �������̽�
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

	virtual void NormalAtk(void) override;
	void BeAttacked(CPlayer * target, int damage);
};