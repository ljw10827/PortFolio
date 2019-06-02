#include "CTeraMapManager.h"
#include "CTeraMap.h"

CTeraMapManager::~CTeraMapManager(void)
{
	for (auto &map : _teraMapList) {
		SAFE_DELETE(map.second);
	}
}

CTeraMap * CTeraMapManager::getTeraMap(const std::string & mapName)
{
	CTeraMap * texture = nullptr;
	auto iterator = _teraMapList.find(mapName);

	if (iterator != _teraMapList.end()) {
		return iterator->second;
	}

	return nullptr;
}

void CTeraMapManager::addTeraMap(const std::string & mapName, CTeraMap * teraMap)
{
	_teraMapList.insert(decltype(_teraMapList)::value_type(mapName, teraMap));
	_currentMapName = mapName;
}
