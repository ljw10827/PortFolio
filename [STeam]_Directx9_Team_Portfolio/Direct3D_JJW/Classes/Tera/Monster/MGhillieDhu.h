#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "CMonster.h"


class MGhillieDhu : public CMonster
{
public:				// public �Լ�

	// ������ & �Ҹ���
	explicit MGhillieDhu(const std::string & monsterName);
	virtual ~MGhillieDhu(void);

	// �������̽�
	virtual void init(void);
	virtual void update(void) override;
	virtual void doDrawObject(void) override;

	virtual void NormalAtk(void) override;
	void BeAttacked(CPlayer * target, int damage);
};