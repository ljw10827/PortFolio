#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CMonster.h"

 
class MArgass : public CMonster
{
public:				// public �Լ�

	// ������ & �Ҹ���
	explicit MArgass(const std::string & monsterName);
	virtual ~MArgass(void);

	// �������̽�
	virtual void init(void);
	virtual void update(void) override;

	virtual void NormalAtk(void) override;
	void BeAttacked(CPlayer * target, int damage);
};