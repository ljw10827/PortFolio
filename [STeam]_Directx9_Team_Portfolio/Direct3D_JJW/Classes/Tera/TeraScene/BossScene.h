#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CSceneObject.h"



class BossScene : public CSceneObject
{
public:		// 인터페이스 구현

	virtual void init(void) override;

	virtual void update(void) override;


public:

	CPlayer * getPlayer(void) { return _player; }

	void BossSoundTrack(void);

	CTeraUI* getTeraUI(void) { return _teraUI; }

private:

	bool _isPlayingBGM = false;
	bool _isStartBattle = false;
	bool _isKilledBoss = false;

	int _initCount = 0;

	int _hitCount = 0;
};