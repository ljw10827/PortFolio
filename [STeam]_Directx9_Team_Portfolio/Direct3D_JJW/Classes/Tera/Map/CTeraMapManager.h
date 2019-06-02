#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../Etc/CTeraGlobalHeader.h"
#include "../Map/filedMap.h"
#include "../Map/bossRoom.h"
#include "../StaticMesh/CStaticMesh_Map.h"

class CTeraMap;

//! �׶�� ������ (�̱���)
class CTeraMapManager
{
public: // �Ҹ���

	virtual ~CTeraMapManager(void);

public:		// public �Լ�

	// getter
	CTeraMap* getTeraMap(const std::string &mapName);

	void addTeraMap(const std::string &mapName, CTeraMap* teraMap);

	std::string getName(void) { return _currentMapName; }

	//! �̱���
	DECLARE_SINGLETON(CTeraMapManager);


private:		// private ����

	std::unordered_map<std::string , CTeraMap*> _teraMapList;

	std::string _currentMapName = "";
};