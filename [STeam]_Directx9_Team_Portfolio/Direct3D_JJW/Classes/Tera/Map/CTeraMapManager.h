#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../Etc/CTeraGlobalHeader.h"
#include "../Map/filedMap.h"
#include "../Map/bossRoom.h"
#include "../StaticMesh/CStaticMesh_Map.h"

class CTeraMap;

//! 테라맵 관리자 (싱글턴)
class CTeraMapManager
{
public: // 소멸자

	virtual ~CTeraMapManager(void);

public:		// public 함수

	// getter
	CTeraMap* getTeraMap(const std::string &mapName);

	void addTeraMap(const std::string &mapName, CTeraMap* teraMap);

	std::string getName(void) { return _currentMapName; }

	//! 싱글턴
	DECLARE_SINGLETON(CTeraMapManager);


private:		// private 변수

	std::unordered_map<std::string , CTeraMap*> _teraMapList;

	std::string _currentMapName = "";
};