#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Interface/IUpdateable.h"
#include "MBasilisk.h"
#include "MVergos.h"
#include "MGhillieDhu.h"
#include "MArgass.h"
#include "MCraftySpider.h"
#include "MDooBean.h"
#include "MPlantMini.h"
#include "MPollutedWolf.h"
#include "../../Global/Utility/Interface/IUpdateable.h"

// TODO

//! 몬스터 팩토리패턴
class CMonsterFactory : public IUpdateable
{
public:			// public 함수

	void init(void);

	// 싱글턴
	DECLARE_SINGLETON(CMonsterFactory);

	// 소멸자
	virtual ~CMonsterFactory(void);
	virtual void update(void) override;

	void CreateBasilisk(int count);
	void CreateGhillieDhu(int count);
	void CreateArgass(int count);
	void CreateCraftySpider(int count);
	void CreateDooBean(int count);
	void CreatePlantMini(int count);
	void CreatePollutedWolf(int count);
	void CreateVergos(void);


public:			// getter setter

	std::vector<CMonster*> getAllMonsterList(void) { return _monsterList; }

	void removeMonster(void);
	void RemoveAllMonster(void);
public:
	void setMonsterCount(int _count) { monsterCount = _count; }
	int getMonsterCount(void) { return monsterCount; }
	void setMonsterTotalCount(int _count) { monsterTotalCount = _count; }
	int getMonsterTotalCount(void) { return monsterTotalCount; }

private:		// private 변수

	std::vector<CMonster *> _monsterList;
	std::vector<CMonster *> _removeList;
	CMonster* _removeObject = nullptr;

private:
	int monsterCount = 0;
	int monsterTotalCount = 0;

	int x = 0;
	int z = 0;
};