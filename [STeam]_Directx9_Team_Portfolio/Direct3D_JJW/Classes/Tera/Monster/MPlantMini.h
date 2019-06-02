#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CMonster.h"


class MPlantMini : public CMonster
{
public:				// public �Լ�

	// ������ & �Ҹ���
	explicit MPlantMini(const std::string & monsterName);
	virtual ~MPlantMini(void);

	// �������̽�
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

	virtual void NormalAtk(void)override;
	void BeAttacked(CPlayer * target, int damage);
	
};