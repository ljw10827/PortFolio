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

// TODO

//! ���� ���丮����
class CMonsterFactory
{
public:			// public �Լ�

	// �̱���
	DECLARE_SINGLETON(CMonsterFactory);

	// �Ҹ���
	virtual ~CMonsterFactory(void);
	void CreateMonster(std::unordered_map<std::string, int> monsterCountList);

public:			// getter setter

	std::vector<MArgass *> getArgassList(void) { return _argassList; }
	std::vector<MBasilisk *> getBasilLiskList(void) { return _basiliskList; }
	std::vector<MCraftySpider *> getCraftySpiderList(void) { return _craftySpiderList; }
	std::vector<MDooBean *> getDooBeanList(void) { return _dooBeanList; }
	std::vector<MGhillieDhu *> getGillieDhuList(void) { return _gillieDhuList; }
	std::vector<MPlantMini *> getPlantMiniList(void) { return _plantMiniList; }
	std::vector<MPollutedWolf *> getPollutedWolf(void) { return _pollutedWolfList; }

	std::vector<MVergos *> getVergosList(void) { return _vergosList; }

	std::vector<CMonster*> getAllMonsterList(void) { return _monsterList; }
public:
	void setMonsterCount(int _count) { monsterCount = _count; }
	int getMonsterCount(void) { return monsterCount; }
	void setMonsterTotalCount(int _count) { monsterTotalCount = _count; }
	int getMonsterTotalCount(void) { return monsterTotalCount; }

private:		// private ����

	std::vector<MArgass *> _argassList;
	std::vector<MBasilisk *> _basiliskList;
	std::vector<MCraftySpider *> _craftySpiderList;
	std::vector<MDooBean *> _dooBeanList;
	std::vector<MGhillieDhu *> _gillieDhuList;
	std::vector<MPlantMini *> _plantMiniList;

	std::vector<MPollutedWolf *> _pollutedWolfList;
	std::vector<MVergos *> _vergosList;

	std::vector<CMonster *> _monsterList;

private:
	int monsterCount = 0;
	int monsterTotalCount = 0;
};