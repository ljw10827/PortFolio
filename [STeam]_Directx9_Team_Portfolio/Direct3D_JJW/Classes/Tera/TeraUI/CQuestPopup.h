#pragma once
#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CUIObject.h"

class CSprite;
class CLabel;
class CTeraEffect;


class CQuestPopup : public CUIObject
{
public:

	enum class QuestProgress
	{
		QUESTZERO,
		QUESTONE = 1,
		QUESTTWO,
		QUESTTHREE,
		QUESTFOUR,
		QUESTFIVE,
		QUESTFINAL = 6,
		NONE
	};

public: //업데이트 drawUI

	virtual void doDrawUI(void) override;

	virtual void update(void) override;

	void setVisible(bool isVisible) { _isVisible = isVisible; }

	CSprite* getNpcQuestSprite(void) { return _quest; }

	bool getisAccept(void) { return _isAccept; }

	QuestProgress setQuestProgress(QuestProgress questProgress) { _questProgress = questProgress; }

	D3DXVECTOR3 setPos(D3DXVECTOR3 pos) { return _playerPos = pos; }

	bool getEnded(void) { return ended; }

public:

public: //생성자

	explicit CQuestPopup();

	virtual ~CQuestPopup();

	void init(void);

private:

	CSprite * _quest = nullptr;
	CLabel * _questLabel = nullptr;
	CLabel * _progressLabel = nullptr;
	CLabel * _progressLabel2 = nullptr;

	char _questString[MAX_PATH] = "";
	char _questString2[MAX_PATH] = "";
	
	bool _isAccept = false;

	int _count = 0;
	int _count2 = 0;
	QuestProgress _questProgress;

	CTeraEffect * _portal = nullptr;

	D3DXVECTOR3 _playerPos;

	int _monsterCount[8] = { 0 };

	bool ended = false;
};
