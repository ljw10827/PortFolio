#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CMonster.h"


class MPollutedWolf : public CMonster
{
public:				// public �Լ�

	// ������ & �Ҹ���
	explicit MPollutedWolf(const std::string & monsterName);
	virtual ~MPollutedWolf(void);

	// �������̽�
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

	virtual void NormalAtk(void) override;

	void BeAttacked(CPlayer * target, int damage);

	float x;
	float z;
};