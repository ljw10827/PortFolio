#pragma once
#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CUIObject.h"

class MBasilik;
class CMonster;
class CSprite;
class CLabel;
class CSprite_MapUI;
class CQuestPopup;

class CTeraUI : public CUIObject
{
public:	
	
	enum class EMapKind
	{
		none = 0,
		mainMap = 1,
		bossMap,
		loading
	};

	struct PopUpCreate
	{
		bool _equipCreate;
		bool _inventoryCreate;
		bool _settingCreate;
	};

	enum class ESkillMiniBoard
	{
		STINGER,
		COMBOATTACK,
		ARMORPASSIVE,
		TENACITY,
		GATHERING,
		CUTTINGSLASH,
		NONE
	};

public: //업데이트 drawUI
	
	virtual void doDrawUI(void) override;

	virtual void update(void) override;

public:

	CSprite* getBossHp(void) { return _bossHpGaugeFull; }

	int getHpPercent(void);
	int getMpPercent(void);

	float getBossHpPercent(void) { return _bossHp; }

	void setMonsterPosition(const D3DXVECTOR3 & _vec);

	void miniMapSetting(void);

	void radarSetting(const D3DXVECTOR3 & a_rtPosition, CSprite_MapUI * target);

	void setHpPercent(int damage);
	void setMpPercent(int amount);

	void setBossHpPercent(int damage);

	void setPlayerPosition(float playerPosX, float playerPosZ);

	void loadingScreenStart(bool isForward);

	bool getLoadingDraw() { return _loadingDraw; }

	bool getStartButtonOver() { return _isStartButtonOver; }

	CSprite* getLoadingBackGround() { return _loadingSprite; }

	CQuestPopup* getQuestPopup() { return _quest; }
	
	void settingBossHpVisible();


	// 인트로
	void mouseOver(void);
	void MainMouseOver(void);

	void iconDraw(void);
	void moveSkillPopUp(void);
	void moveInventoryPopUp(void);
	void moveEquipPopUp(void);

	bool isSkillPopUpCreate(void);
	bool isInventoryPopUpCreate(void);
	bool isEquipPopUpCreate(void);

	void SkillPopUpDraw(void);
	void InventoryPopUpDraw(void);
	void EquipPopUpDraw(void);
	void MiniSkillBoardVisible(void);


public: //생성자

	explicit CTeraUI(EMapKind mapKind);

	virtual ~CTeraUI();

	void init(void);

private:
	CSprite * _hpGaugeFull = nullptr;
	CSprite * _hpGaugeEmpty = nullptr;
	CSprite * _mpGaugeFull = nullptr;
	CSprite * _mpGaugeEmpty = nullptr;
	CSprite * _classTexture = nullptr;
	CSprite * _skillSlot[26];
	CSprite * _centerTexture = nullptr;
	CSprite * _iconSetting = nullptr;
	CSprite * _iconInventory = nullptr;
	CSprite * _iconInventoryOver = nullptr;
	CSprite * _iconSettingOver = nullptr;
	CSprite * _iconEquip = nullptr;
	CSprite * _iconEquipOver = nullptr;

	CLabel * _hpLabel = nullptr;
	CLabel * _mpLabel = nullptr;


	CSprite * _skillPopUp = nullptr;
	CSprite * _inventoryPopUp = nullptr;
	CSprite * _equipPopUp = nullptr;

	CSprite * _stingerMiniBoard = nullptr;
	CSprite * _comboAttackMiniBoard = nullptr;
	CSprite * _armorMiniBoard = nullptr;
	CSprite * _tenacityMiniBoard = nullptr;
	CSprite * _gatheringMiniBoard = nullptr;
	CSprite * _cuttingSlashMiniBoard = nullptr;


	CSprite * _stingerMiniSlot = nullptr;
	CSprite * _comboAttackMiniSlot = nullptr;
	CSprite * _armorMiniSlot = nullptr;
	CSprite * _tenacityMiniSlot = nullptr;
	CSprite * _gatheringMiniSlot = nullptr;
	CSprite * _cuttingSlashMiniSlot = nullptr;


	CSprite * _bossHpGaugeFull = nullptr;
	CSprite * _bossHpGaugeEmpty = nullptr;

	int _playerhp = 4000;
	int _hpPercent = 0;
	int _mpPercent = 0;
	int _playermp = 4000;

	float _bossHp = 20000.0f;
	float _bossHpPercent = 100.0f;

private:
	bool _inventoryOver;
	bool _settingOver;
	bool _equipOver;

	bool _isSkillPress = false;
	bool _isEquipPress = false;
	bool _isInventoryPress = false;

	PopUpCreate _isCreatePopUp;
	POINT _SavePos;

	ESkillMiniBoard _miniBoardType;

	CQuestPopup*  _quest = nullptr;


	// 미니맵 & 레이더

	CSprite_MapUI * m_pMiniMap = nullptr;
	CSprite_MapUI * m_pMiniMapPlayer = nullptr;

	CSprite_MapUI * m_pRadar = nullptr;
	CSprite_MapUI * m_pRadarBase = nullptr;
	CSprite_MapUI * _boss = nullptr;

	std::unordered_map<CMonster *, CSprite_MapUI*> _enemyList;

	SIZE m_miniMapSize;
	SIZE m_totalMapSize;

	SIZE m_RadarSize;
	SIZE m_RadarBaseSize;

	// 마우스의 이전 위치
	POINT m_stPrevMousePosition;

	float m_pRadarAngle = 0;
	bool bIsEnemyDraw = false;

	std::vector<D3DXVECTOR3> enemyLocationList;

	POINT _playerPosition;

	EMapKind _mapKind;

	D3DXVECTOR3 _mobPosition;

	float _offset = 0.0f;

	// 로딩관련
	float _loadingTimer = 0.0f;
	bool _isComplateLoadScene = false;
	bool _isForward = false;
	float _alphaValue = 0.0f;
	bool _loadingDraw = false;

	CSprite* _loadingBackground = nullptr;

	// 인트로 UI
	CSprite * _loadingSprite = nullptr;

	CSprite * _startButton = nullptr;
	CSprite * _exitButton = nullptr;

	bool _isStartButtonOver = false;
	bool _isExitButtonOver = false;

	CSprite * _startButtonOver = nullptr;
	CSprite * _exitButtonOver = nullptr;

	bool _isMouseOver = false;



};
