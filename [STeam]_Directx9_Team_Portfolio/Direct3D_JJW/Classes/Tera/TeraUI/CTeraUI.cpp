#include "CTeraUI.h"
#include "../../Global/Utility/UI/CSprite.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../../Global/Utility/Manager/CSchedulerManager.h"
#include "../../Global/Utility/Object/CCamera.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../../Tera/TeraUI/CQuestPopup.h"

#include "../Monster/CMonster.h"
#include "../Monster/MBasilisk.h"
#include "../Monster/CMonsterFactory.h"

#include "CSprite_MapUI.h"

CTeraUI::CTeraUI(EMapKind mapKind)
	:
	_mapKind(mapKind)
{

}

CTeraUI::~CTeraUI()
{
}

void CTeraUI::init(void)
{
	// 로딩 관련 초기화
	_loadingBackground = new CSprite("Resources/Textures/TeraUI/blackScreen.png");

	if (_mapKind == EMapKind::none) {
		_loadingSprite = new CSprite("Resources/Textures/TeraUI/newLoading1.tga");
		_loadingSprite->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		_startButton = new CSprite("Resources/Textures/TeraUI/startButton.tga");
		_startButton->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f - _startButton->getTextureSize().cx /2.0f,
			GET_WINDOW_SIZE().cy / 1.5f, 0.0f));
		_startButton->setAlphaControl(220);

		_exitButton = new CSprite("Resources/Textures/TeraUI/exitButton.tga");
		_exitButton->setPosition(D3DXVECTOR3(_startButton->getPosition().x,
			_startButton->getPosition().y + 130, 0.0f));
		_exitButton->setAlphaControl(220);

		_startButtonOver = new CSprite("Resources/Textures/TeraUI/startButtonOver.tga");
		_startButtonOver->setPosition(_startButton->getPosition());
		_startButtonOver->setAlphaControl(220);

		_exitButtonOver = new CSprite("Resources/Textures/TeraUI/exitButtonOver.tga");
		_exitButtonOver->setPosition(_exitButton->getPosition());
		_exitButtonOver->setAlphaControl(220);
	}
	else if (_mapKind != EMapKind::none && _mapKind != EMapKind::loading) {
		_miniBoardType = ESkillMiniBoard::NONE;

		_classTexture = new CSprite("Resources/Textures/TeraUI/classTexture.tga");
		_classTexture->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 2.1f) + 20, (GET_WINDOW_SIZE().cy / 1.2f) - 35.f, 0.0f));

		_centerTexture = new CSprite("Resources/Textures/TeraUI/testCenter.tga");
		_centerTexture->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 2.1f) - 15,
			(GET_WINDOW_SIZE().cy / 1.3f), 0.0f));
		_centerTexture->setScaleSprite(D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR2(_centerTexture->getPosition().x, _centerTexture->getPosition().y));

		_hpGaugeEmpty = new CSprite("Resources/Textures/TeraUI/HpGaugeEmpty.png");
		_hpGaugeEmpty->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 3.0f), (GET_WINDOW_SIZE().cy / 1.2f), 0.0f));

		_hpGaugeFull = new CSprite("Resources/Textures/TeraUI/HpGaugeFull.png");
		_hpGaugeFull->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 3.0f), (GET_WINDOW_SIZE().cy / 1.2f), 0.0f));

		_mpGaugeEmpty = new CSprite("Resources/Textures/TeraUI/MpGaugeEmpty.png");
		_mpGaugeEmpty->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 1.8f) - 35, (GET_WINDOW_SIZE().cy / 1.2f), 0.0f));

		_mpGaugeFull = new CSprite("Resources/Textures/TeraUI/MpGaugeFull.png");
		_mpGaugeFull->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 1.8f) - 35, (GET_WINDOW_SIZE().cy / 1.2f), 0.0f));

		_iconSetting = new CSprite("Resources/Textures/TeraUI/IconSetting.png");
		_iconSetting->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 1.0f) - (GET_WINDOW_SIZE().cy * 0.1f) - 3, (GET_WINDOW_SIZE().cy / 1.1f) - 3, 0.0f));

		_iconInventory = new CSprite("Resources/Textures/TeraUI/FinalInvenoryIcon.png");
		_iconInventory->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 1.0f) - (GET_WINDOW_SIZE().cy * 0.1f) - 78, (GET_WINDOW_SIZE().cy / 1.1f), 0.0f));

		_iconEquip = new CSprite("Resources/Textures/TeraUI/IconEquip.png");
		_iconEquip->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 1.0f) - (GET_WINDOW_SIZE().cy * 0.1f) - 153, GET_WINDOW_SIZE().cy / 1.1f, 0.0f));


		_iconSettingOver = new CSprite("Resources/Textures/TeraUI/IconSettingOver.png");
		_iconSettingOver->setPosition(_iconSetting->getPosition());

		_iconInventoryOver = new CSprite("Resources/Textures/TeraUI/IconInventoryOver.png");
		_iconInventoryOver->setPosition(_iconInventory->getPosition());

		_iconEquipOver = new CSprite("Resources/Textures/TeraUI/IconEquipOver.png");
		_iconEquipOver->setPosition(_iconEquip->getPosition());




		for (int i = 0; i < 6; ++i)
		{
			if (i >= 3)
			{
				_skillSlot[i] = new CSprite("Resources/Textures/TeraUI/skillSlot90.tga");
				_skillSlot[i]->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 3.9f) + 90 * (i % 3) + 520,
					(GET_WINDOW_SIZE().cy / 1.1f) - 10, 0.0f));
			}

			else
			{
				_skillSlot[i] = new CSprite("Resources/Textures/TeraUI/skillSlot90.tga");
				_skillSlot[i]->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 3.9f) + 90 * (i % 3) + 160,
					(GET_WINDOW_SIZE().cy / 1.1f) - 10, 0.0f));
			}
		}

		_hpPercent = 100;
		_mpPercent = 100;

		_hpLabel = new CLabel("", 20);
		_hpLabel->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 3.0f), (GET_WINDOW_SIZE().cy / 1.2f) + 30, 0.0f));

		_mpLabel = new CLabel("", 20);
		_mpLabel->setPosition(D3DXVECTOR3((GET_WINDOW_SIZE().cx / 1.8f) - 75 + _mpGaugeFull->getOriginSize().cx, (GET_WINDOW_SIZE().cy / 1.2f) + 30, 0.0f));

		_equipPopUp = new CSprite("Resources/Textures/TeraUI/EquipPopUp.png");
		_equipPopUp->setPosition(D3DXVECTOR3(500.0f, 250, 0.0f));

		_inventoryPopUp = new CSprite("Resources/Textures/TeraUI/InventoryPopUp.png");
		_inventoryPopUp->setPosition(D3DXVECTOR3(300.0f, 125.0f, 0.0f));

		_skillPopUp = new CSprite("Resources/Textures/TeraUI/FinalSkillPopUp.png");
		_skillPopUp->setPosition(D3DXVECTOR3(300.0f, 125.0f, 0.0f));

		_stingerMiniBoard = new CSprite("Resources/Textures/TeraUI/stingerMiniBoard.tga");
		_stingerMiniBoard->setPosition(D3DXVECTOR3(300.0f, 125.0f, 0.0f));
		_stingerMiniBoard->setVisible(false);

		_comboAttackMiniBoard = new CSprite("Resources/Textures/TeraUI/ComboAttackMiniBoard.tga");
		_comboAttackMiniBoard->setPosition(D3DXVECTOR3(450.0f, 125.0f, 0.0f));
		_comboAttackMiniBoard->setVisible(false);

		_armorMiniBoard = new CSprite("Resources/Textures/TeraUI/ArmorMiniBoard.tga");
		_armorMiniBoard->setPosition(D3DXVECTOR3(300.0f, 125.0f, 0.0f));
		_armorMiniBoard->setVisible(false);

		_tenacityMiniBoard = new CSprite("Resources/Textures/TeraUI/TenacityMiniBoard.tga");
		_tenacityMiniBoard->setPosition(D3DXVECTOR3(700.0f, 125.0f, 0.0f));
		_tenacityMiniBoard->setVisible(false);

		_gatheringMiniBoard = new CSprite("Resources/Textures/TeraUI/GatheringMiniBoard.tga");
		_gatheringMiniBoard->setPosition(D3DXVECTOR3(450.0f, 125.0f, 0.0f));
		_gatheringMiniBoard->setVisible(false);

		_cuttingSlashMiniBoard = new CSprite("Resources/Textures/TeraUI/CuttingslashMiniBoard.tga");
		_cuttingSlashMiniBoard->setPosition(D3DXVECTOR3(300.0f, 125.0f, 0.0f));
		_cuttingSlashMiniBoard->setVisible(false);

		_stingerMiniSlot = new CSprite("Resources/Textures/TeraUI/StingerbladeSlot90.tga");
		_stingerMiniSlot->setPosition(D3DXVECTOR3(_skillSlot[0]->getPosition().x + 4, _skillSlot[0]->getPosition().y + 4, 0.0f));
		_stingerMiniSlot->setVisible(true);

		_comboAttackMiniSlot = new CSprite("Resources/Textures/TeraUI/comboattackSlot90.tga");
		_comboAttackMiniSlot->setPosition(D3DXVECTOR3(_skillSlot[1]->getPosition().x + 4, _skillSlot[1]->getPosition().y + 4, 0.0f));
		_comboAttackMiniSlot->setVisible(true);

		_armorMiniSlot = new CSprite("Resources/Textures/TeraUI/ArmorPassivitySlot90.tga");
		_armorMiniSlot->setPosition(D3DXVECTOR3(_skillSlot[2]->getPosition().x + 4, _skillSlot[2]->getPosition().y + 4, 0.0f));
		_armorMiniSlot->setVisible(true);

		_tenacityMiniSlot = new CSprite("Resources/Textures/TeraUI/TenacitySlot90.tga");
		_tenacityMiniSlot->setPosition(D3DXVECTOR3(_skillSlot[3]->getPosition().x + 4, _skillSlot[3]->getPosition().y + 4, 0.0f));
		_tenacityMiniSlot->setVisible(true);

		_gatheringMiniSlot = new CSprite("Resources/Textures/TeraUI/GatheringstrengthSlot90.tga");
		_gatheringMiniSlot->setPosition(D3DXVECTOR3(_skillSlot[4]->getPosition().x + 4, _skillSlot[4]->getPosition().y + 4, 0.0f));
		_gatheringMiniSlot->setVisible(true);

		_cuttingSlashMiniSlot = new CSprite("Resources/Textures/TeraUI/CuttingslashSlot90.tga");
		_cuttingSlashMiniSlot->setPosition(D3DXVECTOR3(_skillSlot[5]->getPosition().x + 4, _skillSlot[5]->getPosition().y + 4, 0.0f));
		_cuttingSlashMiniSlot->setVisible(true);

		_quest = new CQuestPopup();
		_quest->init();

		//==게이지추가 보스

		_bossHpGaugeEmpty = new CSprite("Resources/Textures/TeraUI/bossGageBar.tga");
		_bossHpGaugeEmpty->setVisible(false);
		_bossHpGaugeEmpty->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx /2.0f - _bossHpGaugeEmpty->getOriginSize().cx/2.0f, 100.0f, 0.0f));
		
		_bossHpGaugeFull = new CSprite("Resources/Textures/TeraUI/gageBar.tga");
		_bossHpGaugeFull->setVisible(false);
		_bossHpGaugeFull->setPosition(D3DXVECTOR3(_bossHpGaugeEmpty->getPosition().x +72, 115.0f, 0.0f));


	}

	//! --------------------------------- 미니맵 관련 --------------------------------------//

	if (_mapKind == EMapKind::mainMap){
		// 메인

		m_totalMapSize.cx = 1024;
		m_totalMapSize.cy = 1024;
		// 미니맵으로 사용된 이미지의 실제 크기
		m_miniMapSize.cx = 256;
		m_miniMapSize.cy = 256;

		m_RadarSize.cx = 193;
		m_RadarSize.cy = 194;
		m_RadarBaseSize.cx = 256;
		m_RadarBaseSize.cy = 256;

		m_pMiniMap = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/miniMap3.png");
		m_pMiniMap->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx - m_miniMapSize.cx / 2 - 300, m_miniMapSize.cy / 2 + 350, 0.5f));
		m_pMiniMapPlayer = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/player2.png");

		m_pRadar = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/Rader.tga");
		m_pRadar->SetMapUIPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx - m_RadarSize.cx / 2, m_RadarSize.cy / 2, 0.0f));

		m_pRadarBase = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/RaderBase.png");
		m_pRadarBase->SetMapUIPosition(m_pRadar->getPosition());

		// 몬스터 전체 리스트
		for (auto iterator : GET_MONSTER()->getAllMonsterList()) {
			auto enemy = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/enemy.png");

			auto EnemyPersentX = (iterator->getPosition().x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
			auto EnemyPersentY = 1 - (iterator->getPosition().z + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

			D3DXMATRIXA16 stOffsetMatrix;
			D3DXMatrixTranslation(&stOffsetMatrix,
				m_RadarBaseSize.cx * EnemyPersentX - m_RadarBaseSize.cx / 2.0f,
				m_RadarBaseSize.cy * EnemyPersentY - m_RadarBaseSize.cy / 2.0f,
				0);

			enemy->SetMapUIOffsetPosition(stOffsetMatrix);
			enemy->SetMapUIPosition(D3DXVECTOR3(m_pRadar->GetMapUIPosition().x, m_pRadar->GetMapUIPosition().y, 0.0f));

			_enemyList.insert(decltype(_enemyList)::value_type(iterator, enemy));
		}

		m_stPrevMousePosition = GET_MOUSE_POSITION();

		//this->setMonsterPosition(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
	}
	else if (_mapKind == EMapKind::bossMap) {
		// 보스룸
		// 이 크기가 커지면 레이더에서 잡히는 거리는 실제로 상당한 거리가 있는 느낌으로 된다.
		m_totalMapSize.cx = 512;
		m_totalMapSize.cy = 512;

		m_RadarSize.cx = 193;
		m_RadarSize.cy = 194;
		m_RadarBaseSize.cx = 256;
		m_RadarBaseSize.cy = 256;

		m_pRadar = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/Rader.tga");
		m_pRadar->SetMapUIPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx - m_RadarSize.cx / 2, m_RadarSize.cy / 2, 0.0f));

		m_pRadarBase = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/RaderBase.png");
		m_pRadarBase->SetMapUIPosition(m_pRadar->getPosition());

		_boss = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/enemy.png");

		auto EnemyPersentX = (20.0f + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
		auto EnemyPersentY = 1 - (20.0f + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

		D3DXMATRIXA16 stOffsetMatrix;
		D3DXMatrixTranslation(&stOffsetMatrix,
			m_RadarBaseSize.cx * EnemyPersentX - m_RadarBaseSize.cx / 2.0f,
			m_RadarBaseSize.cy * EnemyPersentY - m_RadarBaseSize.cy / 2.0f,
			0);
		_boss->SetMapUIOffsetPosition(stOffsetMatrix);
		_boss->SetMapUIPosition(D3DXVECTOR3(m_pRadar->GetMapUIPosition().x, m_pRadar->GetMapUIPosition().y, 0.0f));
	}

}


void CTeraUI::doDrawUI(void)
{
	CUIObject::doDrawUI();
	
	if (_mapKind == EMapKind::none) {
		_loadingSprite->drawUI();

		if (_isStartButtonOver)
		{
			_startButtonOver->drawUI();
		}

		else if (!_isStartButtonOver)
		{
			_startButton->drawUI();
		}

		if (_isExitButtonOver)
		{
			_exitButtonOver->drawUI();
		}

		else if (!_isExitButtonOver)
		{
			_exitButton->drawUI();
		}

	}
	else if (_mapKind != EMapKind::none && _mapKind != EMapKind::loading) {
		_centerTexture->drawUI();
		_classTexture->drawUI();
		_hpGaugeEmpty->drawUI();
		_hpGaugeFull->drawUI();
		_mpGaugeEmpty->drawUI();
		_mpGaugeFull->drawUI();
		iconDraw();
		_quest->drawUI();
		_bossHpGaugeEmpty->drawUI();
		_bossHpGaugeFull->drawUI();


		char hpString[MAX_PATH] = "";
		sprintf(hpString, "%d%%", _hpPercent);

		_hpLabel->setString(hpString);

		_hpLabel->drawUI();

		char mpString[MAX_PATH] = "";
		sprintf(mpString, "%d%%", _mpPercent);

		_mpLabel->setString(mpString);

		_mpLabel->drawUI();

		_cuttingSlashMiniSlot->drawUI();
		_gatheringMiniSlot->drawUI();
		_tenacityMiniSlot->drawUI();
		_armorMiniSlot->drawUI();
		_comboAttackMiniSlot->drawUI();
		_stingerMiniSlot->drawUI();


		for (int i = 0; i < 6; ++i)
		{
			_skillSlot[i]->drawUI();
		}
		
		if (GET_DIRECT3D_APPLICATION()->getPressedLCtrl())
		{
			_stingerMiniBoard->drawUI();
			_comboAttackMiniBoard->drawUI();
			_armorMiniBoard->drawUI();
			_tenacityMiniBoard->drawUI();
			_gatheringMiniBoard->drawUI();
			_cuttingSlashMiniBoard->drawUI();
		}
		
		EquipPopUpDraw();
		InventoryPopUpDraw();
		SkillPopUpDraw();
	}

	// 미니맵 관련
	if (_mapKind == EMapKind::mainMap) {
		m_pMiniMap->drawUI();
		m_pMiniMapPlayer->drawUI();
		m_pRadar->drawUI();

		for (auto iterator : _enemyList) {
			if (iterator.first->getState() != CMonster::EState::REMOVE) {
				iterator.second->_isDie = false;
			}
			else if (iterator.first->getState() == CMonster::EState::REMOVE) {
				iterator.second->_isDie = true;
			}

			if (iterator.second->_isDraw) {
				if (!iterator.second->_isDie) {
					iterator.second->drawUI();
				}
			}
		}
	}
	else if (_mapKind == EMapKind::bossMap) {
		m_pRadar->drawUI();
		if (bIsEnemyDraw)
		{
			_boss->drawUI();
		}
	}

	if (_loadingDraw) {
		_loadingBackground->doDrawUI();
	}
}

void CTeraUI::update(void)
{
	CUIObject::update();

	// 로딩 함수 관련
	if (_isComplateLoadScene) {

		// 검은색에서 원색 (정방향)
		if (_isForward) {
			_loadingTimer += GET_DELTA_TIME();

			// 3초동안
			if (_loadingTimer <= 4.0f) {
				_alphaValue -= 255.0f / 4.0f * GET_DELTA_TIME();
				_loadingBackground->setAlphaControl(_alphaValue);
			}
			else {
				// 끝나면
				_loadingDraw = false;
			}
		}
		else {
			// 원색에서 검은색 (역방향)
			_loadingTimer -= GET_DELTA_TIME();

			// 3초동안
			if (_loadingTimer >= 0.0f) {
				_alphaValue += 255.0f / 4.0f * GET_DELTA_TIME();
				_loadingBackground->setAlphaControl(_alphaValue);
			}
			else {
				_loadingDraw = false;
			}
		}
	}

	if (_mapKind == EMapKind::none) {
		mouseOver();

		if (_isExitButtonOver || _isStartButtonOver)
		{
			if (!_isMouseOver) {
				_isMouseOver = true;
				SetCursor(LoadCursorFromFileA("Resources/Cursor/Hand.cur"));
				PLAY_EFFECT_SOUND("Resources/Sounds/ETC/MouseOver.wav");
			}

			if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON) && _isExitButtonOver) {
				PLAY_EFFECT_SOUND("Resources/Sounds/ETC/IntroMenuClick.wav");
				this->loadingScreenStart(false);
				SET_SCHEDULE(4.0f, [=](void) ->void {
					DestroyWindow(GET_WINDOW_HANDLE());
				});
			}
		}
		else {
			_isMouseOver = false;
			SetCursor(LoadCursorFromFileA("Resources/Cursor/Arrow.cur"));
		}
	}
	else if (_mapKind != EMapKind::none && _mapKind != EMapKind::loading) {

		MainMouseOver();
		moveSkillPopUp();
		moveInventoryPopUp();
		moveEquipPopUp();
		MiniSkillBoardVisible();
		_quest->update();


		// TODO : 현재 마우스로 캐릭터를 돌리지 않아서 해당 구문이 동작안함.
		m_stPrevMousePosition = GET_INPUT_MANAGER()->getPrevMousePosition();

		auto stMousePosition = GET_INPUT_MANAGER()->getNowMousePosition();

		// 현재 마우스 위치 확인
		m_pRadarAngle += (float)(stMousePosition.x - m_stPrevMousePosition.x) * 0.1f;
		m_pRadarBase->SetMapUIRotation(-m_pRadarAngle);

		m_stPrevMousePosition = stMousePosition;

	}
	// 미니맵 관련
	if (_mapKind == EMapKind::mainMap) {
		this->miniMapSetting();

		for (auto iterator : _enemyList) {
			this->radarSetting(iterator.first->getPosition(), iterator.second);
		}
	}
	else if (_mapKind == EMapKind::bossMap) {
		this->radarSetting(D3DXVECTOR3(0.0f, 0.0f, 0.0f), _boss);
	}
}


void CTeraUI::setPlayerPosition(float playerPosX, float playerPosZ)
{
	_playerPosition.x = playerPosX;
	_playerPosition.y = playerPosZ;
}

void CTeraUI::loadingScreenStart(bool isForward)
{
	_isForward = isForward;

	if (isForward) {
		_loadingTimer = 0.0f;
		_alphaValue = 255.0f;
	}
	else {
		_loadingTimer = 4.0f;
		_alphaValue = 0.0f;
	}

	_loadingDraw = true;
	_isComplateLoadScene = true;
}

void CTeraUI::setHpPercent(int damage)
{
	_playerhp -= damage;
	_hpPercent -= (100 * damage) / 4000.0f;
	_hpGaugeFull->setRectSize(0, (_hpGaugeFull->getOriginSize().cx / 100.0f) * ((float)_hpPercent), 0, _hpGaugeFull->getOriginSize().cy);
}

void CTeraUI::setMpPercent(int amount)
{
	_playermp -= amount;
	_mpPercent -= (100 * amount) / 3000;
	_mpGaugeFull->setRectSize(0, (_mpGaugeFull->getOriginSize().cx / 100.0f) * ((float)_mpPercent), 0, _mpGaugeFull->getOriginSize().cy);
}

void CTeraUI::setBossHpPercent(int damage)
{
	_bossHp -= damage;

	_bossHpPercent -= (100 * damage) / 20000.0f;
	printf("_bossHP: %f PER : %f \n", _bossHp, _bossHpPercent);
	_bossHpGaugeFull->setRectSize(0, (_bossHpGaugeFull->getOriginSize().cx / 100.0f) * ((float)_bossHpPercent), 0, _bossHpGaugeFull->getOriginSize().cy);
}

void CTeraUI::MainMouseOver(void)
{
	auto stMousePosition = GET_MOUSE_POSITION();
	if (GET_DIRECT3D_APPLICATION()->getPressedLCtrl())
	{
		if ((GET_MOUSE_POSITION().x >= _iconInventory->getPosition().x + 15) && (GET_MOUSE_POSITION().x <= _iconInventory->getPosition().x + _iconInventory->getOriginSize().cx - 15))
		{
			if ((GET_MOUSE_POSITION().y >= _iconInventory->getPosition().y + 10) &&
				(GET_MOUSE_POSITION().y <= _iconInventory->getPosition().y + _iconInventory->getOriginSize().cy - 3))
			{
				_inventoryOver = true;
				_settingOver = false;
				_equipOver = false;
			}
		}

		else if ((GET_MOUSE_POSITION().x >= _iconSetting->getPosition().x + 15) && (GET_MOUSE_POSITION().x <= _iconSetting->getPosition().x + _iconSetting->getOriginSize().cx - 15))
		{
			if ((GET_MOUSE_POSITION().y >= _iconSetting->getPosition().y + 10) &&
				(GET_MOUSE_POSITION().y <= _iconSetting->getPosition().y + _iconSetting->getOriginSize().cy - 3))
			{
				_inventoryOver = false;
				_settingOver = true;
				_equipOver = false;
			}
		}

		else if ((GET_MOUSE_POSITION().x >= _iconEquip->getPosition().x + 15) && (GET_MOUSE_POSITION().x <= _iconEquip->getPosition().x + _iconEquip->getOriginSize().cx - 15))
		{
			if ((GET_MOUSE_POSITION().y >= _iconEquip->getPosition().y + 10) &&
				(GET_MOUSE_POSITION().y <= _iconEquip->getPosition().y + _iconEquip->getOriginSize().cy - 3))
			{
				_inventoryOver = false;
				_settingOver = false;
				_equipOver = true;
			}
		}

		else
		{
			_inventoryOver = false;
			_settingOver = false;
			_equipOver = false;
		}
	}
	
	else if (!GET_DIRECT3D_APPLICATION()->getPressedLCtrl())
	{
		_inventoryOver = false;
		_settingOver = false;
		_equipOver = false;
	}

	if ((GET_MOUSE_POSITION().y >= _skillSlot[0]->getPosition().y) &&
		(GET_MOUSE_POSITION().y <= _skillSlot[0]->getPosition().y + _skillSlot[0]->getOriginSize().cy))
	{
		if ((GET_MOUSE_POSITION().x >= _stingerMiniSlot->getPosition().x) &&
			(GET_MOUSE_POSITION().x <= _stingerMiniSlot->getPosition().x + _stingerMiniSlot->getOriginSize().cx))
		{
			_miniBoardType = ESkillMiniBoard::STINGER;
		}

		else if ((GET_MOUSE_POSITION().x >= _comboAttackMiniSlot->getPosition().x) &&
			(GET_MOUSE_POSITION().x <= _comboAttackMiniSlot->getPosition().x + _comboAttackMiniSlot->getOriginSize().cx))
		{
			_miniBoardType = ESkillMiniBoard::COMBOATTACK;
		}

		else if ((GET_MOUSE_POSITION().x >= _armorMiniSlot->getPosition().x) &&
			(GET_MOUSE_POSITION().x <= _armorMiniSlot->getPosition().x + _armorMiniSlot->getOriginSize().cx))
		{
			_miniBoardType = ESkillMiniBoard::ARMORPASSIVE;
		}

		else if ((GET_MOUSE_POSITION().x >= _tenacityMiniSlot->getPosition().x) &&
			(GET_MOUSE_POSITION().x <= _tenacityMiniSlot->getPosition().x + _tenacityMiniSlot->getOriginSize().cx))
		{
			_miniBoardType = ESkillMiniBoard::TENACITY;
		}

		else if ((GET_MOUSE_POSITION().x >= _gatheringMiniSlot->getPosition().x) &&
			(GET_MOUSE_POSITION().x <= _gatheringMiniSlot->getPosition().x + _gatheringMiniSlot->getOriginSize().cx))
		{
			_miniBoardType = ESkillMiniBoard::GATHERING;
		}

		else if ((GET_MOUSE_POSITION().x >= _cuttingSlashMiniSlot->getPosition().x) &&
			(GET_MOUSE_POSITION().x <= _cuttingSlashMiniSlot->getPosition().x + _cuttingSlashMiniSlot->getOriginSize().cx))
		{
			_miniBoardType = ESkillMiniBoard::CUTTINGSLASH;
		}

		else
		{
			_miniBoardType = ESkillMiniBoard::NONE;
		}
	}

	else
	{
		_miniBoardType = ESkillMiniBoard::NONE;

	}

}

void CTeraUI::iconDraw(void)
{
	if (_inventoryOver)
	{
		_iconInventoryOver->drawUI();
	}
	else if (!_inventoryOver)
	{
		_iconInventory->drawUI();
	}

	if (_settingOver)
	{
		_iconSettingOver->drawUI();
	}
	else if (!_settingOver)
	{
		_iconSetting->drawUI();
	}

	if (_equipOver)
	{
		_iconEquipOver->drawUI();
	}
	else if (!_equipOver)
	{
		_iconEquip->drawUI();
	}
}

void CTeraUI::moveSkillPopUp(void)
{
	if (_isCreatePopUp._settingCreate)
	{


		if ((GET_MOUSE_POSITION().x >= _skillPopUp->getPosition().x &&
			GET_MOUSE_POSITION().x <= _skillPopUp->getPosition().x + _skillPopUp->getOriginSize().cx) &&
			(GET_MOUSE_POSITION().y >= _skillPopUp->getPosition().y
				&& GET_MOUSE_POSITION().y <= _skillPopUp->getPosition().y + (_skillPopUp->getOriginSize().cy / 8.9f)))
		{
			if (IS_MOUSE_DOWN((int)EMouseInput::LEFT_BUTTON))
			{
				if (!_isSkillPress)
				{
					_SavePos = GET_MOUSE_POSITION();

					_SavePos.x = _SavePos.x - _skillPopUp->getPosition().x;


					_SavePos.y = _SavePos.y - _skillPopUp->getPosition().y;


					_isSkillPress = true;
				}
			}
		}
		if (_isSkillPress)
		{
			auto SpritePos = GET_MOUSE_POSITION();
			SpritePos.x = SpritePos.x - _SavePos.x;
			SpritePos.y = SpritePos.y - _SavePos.y;

			_skillPopUp->setPosition(D3DXVECTOR3(SpritePos.x, SpritePos.y, 0.0f));
		}

		if (IS_MOUSE_RELEASED((int)EMouseInput::LEFT_BUTTON))
		{
			if (_isSkillPress)
			{
				_isSkillPress = false;
			}
		}

	}
}

void CTeraUI::moveInventoryPopUp(void)
{
	if (_isCreatePopUp._inventoryCreate)
	{
		if ((GET_MOUSE_POSITION().x >= _inventoryPopUp->getPosition().x &&
			GET_MOUSE_POSITION().x <= _inventoryPopUp->getPosition().x + _inventoryPopUp->getOriginSize().cx) &&
			(GET_MOUSE_POSITION().y >= _inventoryPopUp->getPosition().y
				&& GET_MOUSE_POSITION().y <= _inventoryPopUp->getPosition().y + (_inventoryPopUp->getOriginSize().cy / 8.9f)))
		{
			if (IS_MOUSE_DOWN((int)EMouseInput::LEFT_BUTTON))
			{
				if (!_isInventoryPress)
				{
					_SavePos = GET_MOUSE_POSITION();

					_SavePos.x = _SavePos.x - _inventoryPopUp->getPosition().x;


					_SavePos.y = _SavePos.y - _inventoryPopUp->getPosition().y;


					_isInventoryPress = true;
				}
			}
		}
		if (_isInventoryPress)
		{
			auto SpritePos = GET_MOUSE_POSITION();
			SpritePos.x = SpritePos.x - _SavePos.x;
			SpritePos.y = SpritePos.y - _SavePos.y;

			_inventoryPopUp->setPosition(D3DXVECTOR3(SpritePos.x, SpritePos.y, 0.0f));
		}

		if (IS_MOUSE_RELEASED((int)EMouseInput::LEFT_BUTTON))
		{
			if (_isInventoryPress)
			{
				_isInventoryPress = false;
			}
		}

	}
}

void CTeraUI::moveEquipPopUp(void)
{
	if (_isCreatePopUp._equipCreate)
	{


		if ((GET_MOUSE_POSITION().x >= _equipPopUp->getPosition().x &&
			GET_MOUSE_POSITION().x <= _equipPopUp->getPosition().x + _equipPopUp->getOriginSize().cx) &&
			(GET_MOUSE_POSITION().y >= _equipPopUp->getPosition().y
				&& GET_MOUSE_POSITION().y <= _equipPopUp->getPosition().y + (_equipPopUp->getOriginSize().cy / 8.9f)))
		{
			if (IS_MOUSE_DOWN((int)EMouseInput::LEFT_BUTTON))
			{
				if (!_isEquipPress)
				{
					_SavePos = GET_MOUSE_POSITION();

					_SavePos.x = _SavePos.x - _equipPopUp->getPosition().x;


					_SavePos.y = _SavePos.y - _equipPopUp->getPosition().y;


					_isEquipPress = true;
				}
			}
		}
		if (_isEquipPress)
		{
			auto SpritePos = GET_MOUSE_POSITION();
			SpritePos.x = SpritePos.x - _SavePos.x;
			SpritePos.y = SpritePos.y - _SavePos.y;

			_equipPopUp->setPosition(D3DXVECTOR3(SpritePos.x, SpritePos.y, 0.0f));
		}

		if (IS_MOUSE_RELEASED((int)EMouseInput::LEFT_BUTTON))
		{
			if (_isEquipPress)
			{
				_isEquipPress = false;
			}
		}

	}
}

bool CTeraUI::isSkillPopUpCreate(void)
{
	if (!_isCreatePopUp._settingCreate)
	{
		if (_settingOver)
		{
			if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
			{
				_isCreatePopUp._settingCreate = true;
			}
		}
	}

	else if (_isCreatePopUp._settingCreate)
	{
		if (_settingOver)
		{
			if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
			{
				_isCreatePopUp._settingCreate = false;
			}
		}
	}

	return _isCreatePopUp._settingCreate;
}

bool CTeraUI::isInventoryPopUpCreate(void)
{
	if (!_isCreatePopUp._inventoryCreate)
	{
		if (_inventoryOver)
		{
			if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
			{
				_isCreatePopUp._inventoryCreate = true;
			}
		}
	}

	else if (_isCreatePopUp._inventoryCreate)
	{
		if (_inventoryOver)
		{
			if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
			{
				_isCreatePopUp._inventoryCreate = false;
			}
		}
	}

	return _isCreatePopUp._inventoryCreate;
}

bool CTeraUI::isEquipPopUpCreate(void)
{
	if (!_isCreatePopUp._equipCreate)
	{
		if (_equipOver)
		{
			if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
			{
				_isCreatePopUp._equipCreate = true;
			}
		}
	}

	else if (_isCreatePopUp._equipCreate)
	{
		if (_equipOver)
		{
			if (GET_MOUSE_POSITION().x)
				if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
				{
					_isCreatePopUp._equipCreate = false;
				}
		}
	}

	return _isCreatePopUp._equipCreate;
}

void CTeraUI::SkillPopUpDraw(void)
{
	if (isSkillPopUpCreate())
	{
		_skillPopUp->drawUI();
	}
}

void CTeraUI::InventoryPopUpDraw(void)
{
	if (isInventoryPopUpCreate())
	{
		_inventoryPopUp->drawUI();
	}
}

void CTeraUI::EquipPopUpDraw(void)
{
	if (isEquipPopUpCreate())
	{
		_equipPopUp->drawUI();
	}
}

void CTeraUI::MiniSkillBoardVisible(void)
{
	switch (_miniBoardType)
	{
	case CTeraUI::ESkillMiniBoard::STINGER:
	{
		_stingerMiniBoard->setVisible(true);
		_comboAttackMiniBoard->setVisible(false);
		_armorMiniBoard->setVisible(false);
		_tenacityMiniBoard->setVisible(false);
		_gatheringMiniBoard->setVisible(false);
		_cuttingSlashMiniBoard->setVisible(false);

		_stingerMiniBoard->setPosition(D3DXVECTOR3(_skillSlot[0]->getPosition().x + (_skillSlot[0]->getOriginSize().cx / 2.0f) - (_stingerMiniBoard->getOriginSize().cx),
			_skillSlot[0]->getPosition().y + (_skillSlot[0]->getOriginSize().cy / 2.0f) - (_stingerMiniBoard->getOriginSize().cy), 0.0f));

		break;
	}
	case CTeraUI::ESkillMiniBoard::COMBOATTACK:
	{
		_stingerMiniBoard->setVisible(false);
		_comboAttackMiniBoard->setVisible(true);
		_armorMiniBoard->setVisible(false);
		_tenacityMiniBoard->setVisible(false);
		_gatheringMiniBoard->setVisible(false);
		_cuttingSlashMiniBoard->setVisible(false);

		_comboAttackMiniBoard->setPosition(D3DXVECTOR3(_skillSlot[1]->getPosition().x + (_skillSlot[1]->getOriginSize().cx / 2.0f) - (_comboAttackMiniBoard->getOriginSize().cx),
			_skillSlot[1]->getPosition().y + (_skillSlot[1]->getOriginSize().cy / 2.0f) - (_comboAttackMiniBoard->getOriginSize().cy), 0.0f));

		break;
	}
	case CTeraUI::ESkillMiniBoard::ARMORPASSIVE:
	{
		_stingerMiniBoard->setVisible(false);
		_comboAttackMiniBoard->setVisible(false);
		_armorMiniBoard->setVisible(true);
		_tenacityMiniBoard->setVisible(false);
		_gatheringMiniBoard->setVisible(false);
		_cuttingSlashMiniBoard->setVisible(false);

		_armorMiniBoard->setPosition(D3DXVECTOR3(_skillSlot[2]->getPosition().x + (_skillSlot[2]->getOriginSize().cx / 2.0f) - (_armorMiniBoard->getOriginSize().cx),
			_skillSlot[2]->getPosition().y + (_skillSlot[2]->getOriginSize().cy / 2.0f) - (_armorMiniBoard->getOriginSize().cy), 0.0f));

		break;
	}
	case CTeraUI::ESkillMiniBoard::TENACITY:
	{
		_stingerMiniBoard->setVisible(false);
		_comboAttackMiniBoard->setVisible(false);
		_armorMiniBoard->setVisible(false);
		_tenacityMiniBoard->setVisible(true);
		_gatheringMiniBoard->setVisible(false);
		_cuttingSlashMiniBoard->setVisible(false);

		_tenacityMiniBoard->setPosition(D3DXVECTOR3(_skillSlot[3]->getPosition().x + (_skillSlot[3]->getOriginSize().cx / 2.0f) - (_tenacityMiniBoard->getOriginSize().cx),
			_skillSlot[3]->getPosition().y + (_skillSlot[3]->getOriginSize().cy / 2.0f) - (_tenacityMiniBoard->getOriginSize().cy), 0.0f));

		break;
	}
	case CTeraUI::ESkillMiniBoard::GATHERING:
	{
		_stingerMiniBoard->setVisible(false);
		_comboAttackMiniBoard->setVisible(false);
		_armorMiniBoard->setVisible(false);
		_tenacityMiniBoard->setVisible(false);
		_gatheringMiniBoard->setVisible(true);
		_cuttingSlashMiniBoard->setVisible(false);

		_gatheringMiniBoard->setPosition(D3DXVECTOR3(_skillSlot[4]->getPosition().x + (_skillSlot[4]->getOriginSize().cx / 2.0f) - (_gatheringMiniBoard->getOriginSize().cx),
			_skillSlot[4]->getPosition().y + (_skillSlot[4]->getOriginSize().cy / 2.0f) - (_gatheringMiniBoard->getOriginSize().cy), 0.0f));

		break;
	}
	case CTeraUI::ESkillMiniBoard::CUTTINGSLASH:
	{
		_stingerMiniBoard->setVisible(false);
		_comboAttackMiniBoard->setVisible(false);
		_armorMiniBoard->setVisible(false);
		_tenacityMiniBoard->setVisible(false);
		_gatheringMiniBoard->setVisible(false);
		_cuttingSlashMiniBoard->setVisible(true);

		_cuttingSlashMiniBoard->setPosition(D3DXVECTOR3(_skillSlot[5]->getPosition().x + (_skillSlot[5]->getOriginSize().cx / 2.0f) - (_cuttingSlashMiniBoard->getOriginSize().cx),
			_skillSlot[5]->getPosition().y + (_skillSlot[5]->getOriginSize().cy / 2.0f) - (_cuttingSlashMiniBoard->getOriginSize().cy), 0.0f));

		break;
	}
	case CTeraUI::ESkillMiniBoard::NONE:
	{
		_stingerMiniBoard->setVisible(false);
		_comboAttackMiniBoard->setVisible(false);
		_armorMiniBoard->setVisible(false);
		_tenacityMiniBoard->setVisible(false);
		_gatheringMiniBoard->setVisible(false);
		_cuttingSlashMiniBoard->setVisible(false);

		break;
	}
	default:
	{
		//DO NOTHING
		break;
	}
	}
}


int CTeraUI::getHpPercent(void)
{
	return _playerhp;
}

int CTeraUI::getMpPercent(void)
{
	return _mpPercent;
}


//////////////////////// 미니맵관련

void CTeraUI::setMonsterPosition(const D3DXVECTOR3 & _vec)
{
	enemyLocationList.push_back(_vec);
}

void CTeraUI::miniMapSetting(void)
{
	auto playerPersentX = (_playerPosition.x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
	auto playerPersentY = 1 - (_playerPosition.y + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

	auto playerXPosition = m_miniMapSize.cx * playerPersentX + m_pMiniMap->getPosition().x - m_miniMapSize.cx / 2;
	auto playerYPosition = m_miniMapSize.cy * playerPersentY + m_pMiniMap->getPosition().y - m_miniMapSize.cy / 2;

	m_pMiniMapPlayer->SetMapUIPosition(D3DXVECTOR3(playerXPosition, playerYPosition, 0.0f));
}

void CTeraUI::radarSetting(const D3DXVECTOR3 & a_rtPosition, CSprite_MapUI * target)
{
	// 레이더 세팅
	if (_mapKind == EMapKind::mainMap) {
		auto playerPersentX = (_playerPosition.x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
		auto playerPersentY = 1 - (_playerPosition.y + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

		auto playerXPosition = m_miniMapSize.cx * playerPersentX;
		auto playerYPosition = m_miniMapSize.cy * playerPersentY;

		target->SetMapUIRotation(-m_pRadarAngle);


		auto moveLengthX = playerXPosition - m_miniMapSize.cx / 2.0f;
		auto moveLengthY = playerYPosition - m_miniMapSize.cy / 2.0f;

		auto EnemyPersentX = (a_rtPosition.x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
		auto EnemyPersentY = 1 - (a_rtPosition.z + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

		auto enemyXPositionX = m_RadarBaseSize.cx * EnemyPersentX + m_pRadarBase->GetMapUIPosition().x - m_RadarBaseSize.cx / 2.0f;
		auto enemyYPositionY = m_RadarBaseSize.cy * EnemyPersentY + m_pRadarBase->GetMapUIPosition().y - m_RadarBaseSize.cy / 2.0f;

		auto enemyXFinalPositionX = (float)GET_WINDOW_SIZE().cx - enemyXPositionX - m_RadarBaseSize.cx / 2.0f;
		auto enemyXFinalPositionY = enemyYPositionY - m_RadarBaseSize.cy / 2.0f;

		auto enemyLocationX = -(m_RadarBaseSize.cx / 2.0f - m_RadarBaseSize.cx * EnemyPersentX) - moveLengthX;
		auto enemyLocationY = -(m_RadarBaseSize.cy / 2.0f - m_RadarBaseSize.cy * EnemyPersentY) - moveLengthY;

		D3DXMATRIXA16 stOffsetMatrix;
		D3DXMatrixTranslation(&stOffsetMatrix,
			enemyLocationX,
			enemyLocationY,
			0);

		target->SetMapUIOffsetPosition(stOffsetMatrix);

		auto enemyTruePositionX = target->GetMapUIPosition().x - enemyLocationX;
		auto enemyTruePositionY = target->GetMapUIPosition().y - enemyLocationY;

		D3DXVECTOR3 stenemyTruePosition = {
		enemyTruePositionX,
		enemyTruePositionY,
		0.0f
		};

		auto radarVisitDitance = m_pRadar->GetMapUIPosition() - stenemyTruePosition;

		if (D3DXVec3Length(&radarVisitDitance) <= (m_RadarSize.cx / 2.0f) - 30.0f) {
			target->_isDraw = true;
		}
		else {
			target->_isDraw = false;
		}
	}
	else if (_mapKind == EMapKind::bossMap) {
		auto playerPersentX = (_playerPosition.x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
		auto playerPersentY = 1 - (_playerPosition.y + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

		auto playerXPosition = m_RadarSize.cx * playerPersentX;
		auto playerYPosition = m_RadarSize.cy * playerPersentY;

		target->SetMapUIRotation(-m_pRadarAngle);

		auto moveLengthX = playerXPosition - m_RadarSize.cx / 2.0f;
		auto moveLengthY = playerYPosition - m_RadarSize.cy / 2.0f;

		auto EnemyPersentX = (a_rtPosition.x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
		auto EnemyPersentY = 1 - (a_rtPosition.z + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

		auto enemyLocationX = -(m_RadarBaseSize.cx / 2.0f - m_RadarBaseSize.cx * EnemyPersentX) - moveLengthX;
		auto enemyLocationY = -(m_RadarBaseSize.cy / 2.0f - m_RadarBaseSize.cy * EnemyPersentY) - moveLengthY;

		D3DXMATRIXA16 stOffsetMatrix;
		D3DXMatrixTranslation(&stOffsetMatrix,
			enemyLocationX,
			enemyLocationY,
			0);
		_boss->SetMapUIOffsetPosition(stOffsetMatrix);

		auto enemyTruePositionX = _boss->GetMapUIPosition().x - enemyLocationX;
		auto enemyTruePositionY = _boss->GetMapUIPosition().y - enemyLocationY;
		D3DXVECTOR3 stenemyTruePosition = {
			enemyTruePositionX,
			enemyTruePositionY,
			0.0f
		};

		auto radarVisitDitance = m_pRadar->GetMapUIPosition() - stenemyTruePosition;
		if (D3DXVec3Length(&radarVisitDitance) <= m_RadarSize.cx / 2.0f - 30.0f) // 레이더안의 원의 반지름을 얼추 맞추기 위한 조정
		{
			bIsEnemyDraw = true;
		}
		else
		{
			bIsEnemyDraw = false;
		}
	}
	
}


void CTeraUI::settingBossHpVisible()
{
	_bossHpGaugeFull->setVisible(true);
	_bossHpGaugeEmpty->setVisible(true);
}

void CTeraUI::mouseOver(void)
{
	auto stMousePosition = GET_MOUSE_POSITION();

	if ((GET_MOUSE_POSITION().x >= _startButton->getPosition().x) && (GET_MOUSE_POSITION().x <= _startButton->getPosition().x + _startButton->getOriginSize().cx))
	{

		if ((GET_MOUSE_POSITION().y >= _startButton->getPosition().y) &&
			(GET_MOUSE_POSITION().y <= _startButton->getPosition().y + _startButton->getOriginSize().cy))
		{
			_isStartButtonOver = true;
			_isExitButtonOver = false;
		}

		else if ((GET_MOUSE_POSITION().y >= _exitButton->getPosition().y) &&
			(GET_MOUSE_POSITION().y <= _exitButton->getPosition().y + _exitButton->getOriginSize().cy))
		{
			_isStartButtonOver = false;
			_isExitButtonOver = true;
		}

		else
		{
			_isStartButtonOver = false;
			_isExitButtonOver = false;
		}
	}
	else
	{
		_isStartButtonOver = false;
		_isExitButtonOver = false;
	}
}

