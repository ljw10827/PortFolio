#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CSceneObject.h"

class CSkinnedMesh;
class CLabel;
class CTeraEffect;
class filedMap;
class CSkinnedMeshNPC;
class CMonster;

class MainScene : public CSceneObject
{
public:
	explicit MainScene(void);
	virtual ~MainScene(void);
	

public:		// 인터페이스 구현

	virtual void init(void) override;

	virtual void update(void) override;

	CTeraUI* getTeraUI(void) { return _teraUI; }

	D3DXVECTOR3 getPlayerPosition(void) { return _player->getPosition(); }

	CPlayer * getPlayer(void) { return _player; }

	CTeraEffect* getPortal(void) { return _portal; }

	void setCompletedAllQuest(bool isComplete) { _completedAllQuest = isComplete; }

private: // private 변수

	CTeraEffect* _portal = nullptr;

	bool _isMove = false;
	float _volume = 1.0f;
	float _subBGMTimer = 0.0f;
	bool _isPlayingBGM = false;
	int _initCount = 1;

	float _hitCount = 0.0f;

	bool _completedAllQuest = false;
};