#include "CQuestPopup.h"
#include "../../Global/Utility/UI/CSprite.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../../Tera/Monster/CMonsterFactory.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Base/CWindowApplication.h"
#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../TeraScene/MainScene.h"
#include "../Map/CTeraMapManager.h"
#include "../NPC/CNPC.h"


#define MAX_DOOBEAN 3
#define MAX_PLANT 3
#define MAX_ARGASS 3
#define MAX_GHILLIEDHU 3
#define MAX_POLLUTEDWOLF 3
#define MAX_CRAFTYSPIDER 3
#define MAX_BASILISK 1
#define MAX_VERGOS 1



CQuestPopup::CQuestPopup()
{

}

CQuestPopup::~CQuestPopup()
{
	SAFE_DELETE(_quest);
}


void CQuestPopup::init(void)
{
	_quest = new CSprite("Resources/Textures/TeraUI/Quest.tga");
	_quest->setPosition(D3DXVECTOR3(100.0f, 300.0f, 0.0f));
	_quest->setScaleSprite(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR2(_quest->getPosition().x, _quest->getPosition().y));
	_quest->setVisible(false);

	_questLabel = new CLabel("퀘스트", 30);
	_questLabel->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx * 0.85, 230.0f, 0.0f));
	_questLabel->setVisible(false);

	_questProgress = QuestProgress::QUESTZERO;
	sprintf(_questString, "%d.마을에 이상현상이 발견되었다. \n  마을에 있는 장군에게 가보자.", (int)_questProgress);
	
	_progressLabel = new CLabel(_questString, 16);
	_progressLabel->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx * 0.85, 260.0f, 0.0f));
	_progressLabel->setVisible(true);

	_progressLabel2 = new CLabel(_questString2, 13);
	_progressLabel2->setPosition(D3DXVECTOR3(1030.0f, 270.0f, 0.0f));
	_progressLabel2->setVisible(false);

	_portal = new CTeraEffect(L"Resources/Effekseers/Portal3.efk");
	_portal->setDeltaTime(0.05f);
}


void CQuestPopup::doDrawUI(void)
{
	CUIObject::doDrawUI();
	
	_quest->drawUI();
	_questLabel->drawUI();
	_progressLabel->drawUI();
	_progressLabel2->drawUI();
	_portal->draw();

}

void CQuestPopup::update(void)
{
	CUIObject::update();

	_portal->update();

	if ((bossRoom*)GET_MAP("BossMap") != nullptr) {
		_isAccept = true;
		_questProgress = QuestProgress::QUESTFINAL;
		sprintf(_questString, "\n%d.고룡 베르고스 사냥하기. \n\n 고룡 베르고스 : %d / %d ", (int)_questProgress,
			0, MAX_VERGOS);
		_progressLabel->setString(_questString);
	}

	if (_quest->getVisible())
	{
		if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
		{
			auto mousePosition = GET_MOUSE_POSITION();
			printf("%d, %d \n", mousePosition.x, mousePosition.y);
			printf("%f, %f \n", _quest->getPosition().x, _quest->getPosition().y);
			if ((mousePosition.x >= _quest->getPosition().x + 145 && mousePosition.x <= _quest->getPosition().x + 205)
				&& (mousePosition.y >= _quest->getPosition().y + 244 && mousePosition.y <= _quest->getPosition().y + 255))
			{
				if (!_isAccept)
				{
					_questProgress = QuestProgress::QUESTONE;
					sprintf(_questString, "%d.마을 주변에 있는 몬스터 조사하기. \n\n 식인 플랜트 : %d / %d", (int)_questProgress, 0, MAX_PLANT);
					_progressLabel->setString(_questString);
					_isAccept = true;
				}
			}
		}
	}

	if (_isAccept)
	{
		_quest->setVisible(false);
		_questLabel->setVisible(true);
		_progressLabel->setVisible(true);
		_progressLabel2->setVisible(true);

		// 마리수 카운트
		int monsterCount[8] = { 0 };

		for (auto &iter : GET_MONSTER()->getAllMonsterList()) {
			if (iter->getVisible()) {
				if (iter->getMonsterName() == "M_Argass") 		monsterCount[0]++;
				if (iter->getMonsterName() == "M_Basilisk")		monsterCount[1]++;
				if (iter->getMonsterName() == "M_CraftySpider")	monsterCount[2]++;
				if (iter->getMonsterName() == "M_DooBean")		monsterCount[3]++;
				if (iter->getMonsterName() == "M_GhillieDhu")	monsterCount[4]++;
				if (iter->getMonsterName() == "M_Plant_mini")	monsterCount[5]++;
				if (iter->getMonsterName() == "M_PollutedWolf")	monsterCount[6]++;
				if (iter->getMonsterName() == "M_Vergos")		monsterCount[7]++;
			}
		}
		
		for (int i = 0; i < 8; ++i) {
			_monsterCount[i] = monsterCount[i];
		}


		switch (_questProgress)
		{
		case CQuestPopup::QuestProgress::QUESTONE:
		{
			sprintf(_questString, "\n%d.마을 주변에 있는 몬스터 조사하기. \n\n식인 플랜트 : %d / %d", (int)_questProgress,
				CREATE_MAX_PLANT - _monsterCount[5], MAX_PLANT);


			if ((CREATE_MAX_PLANT - _monsterCount[5]) >= MAX_PLANT)
			{
				_questProgress = QuestProgress::QUESTTWO;
				sprintf(_questString, "\n%d.마을 주변에 있는 몬스터 조사하기. \n\n길리두 : %d / %d", (int)_questProgress, 0, MAX_GHILLIEDHU);
			}

			_progressLabel->setString(_questString);

			break;
		}
		case CQuestPopup::QuestProgress::QUESTTWO:
		{
			sprintf(_questString, "\n%d.마을 주변에 있는 몬스터 조사하기. \n\n길리두 : %d / %d", (int)_questProgress, CREATE_MAX_GHILLIEDHU - _monsterCount[4], MAX_GHILLIEDHU);

			if ((CREATE_MAX_GHILLIEDHU - _monsterCount[4]) >= MAX_GHILLIEDHU)
			{
				_questProgress = QuestProgress::QUESTTHREE;
				sprintf(_questString, "\n%d.마을 주변에 있는 몬스터 조사하기. \n\n 크래피티 스파이더 : %d / %d ", (int)_questProgress,
					0, MAX_CRAFTYSPIDER);
			}

			_progressLabel->setString(_questString);

			break;
		}
		case CQuestPopup::QuestProgress::QUESTTHREE:
		{
			sprintf(_questString, "\n%d.마을 주변에 있는 몬스터 조사하기. \n\n 크래피티 스파이더 : %d / %d", (int)_questProgress,
				CREATE_MAX_CRAFTYSPIDER - _monsterCount[2], MAX_CRAFTYSPIDER);

			if ((CREATE_MAX_CRAFTYSPIDER - _monsterCount[2]) >= MAX_CRAFTYSPIDER)
			{
				_questProgress = QuestProgress::QUESTFOUR;
				sprintf(_questString, "%d.마을 주변에 있는 몬스터 조사하기. \n\n 바실리스크 : %d / %d ", (int)_questProgress,
					0, MAX_BASILISK);
			}

			_progressLabel->setString(_questString);
			break;
		}

		case CQuestPopup::QuestProgress::QUESTFOUR:
		{
			sprintf(_questString, "\n%d.마을 주변에 있는 몬스터 조사하기. \n\n 바실리스크 : %d / %d ", (int)_questProgress,
				CREATE_MAX_BASILISK - _monsterCount[1], MAX_BASILISK);

			if ((CREATE_MAX_BASILISK - _monsterCount[1]) >= MAX_BASILISK)
			{
				_questProgress = QuestProgress::QUESTFIVE;
				sprintf(_questString, "\n%d.마을 어딘가에 생성된 포탈에 들어가자.", (int)_questProgress);

				auto pos = D3DXVECTOR3(375.0f, 0.0f, -305.0f);
				pos.y = GET_MAP("FieldMap")->getHeightMapY(pos) + 1.0f;
				_portal->playEffeckseer(D3DXVECTOR3(197.0f, pos.y, -170.0f));
				_portal->setScaleEffekseer(1.0f, 1.5f, 2.0f);
			}

			_progressLabel->setString(_questString);
			break;
		}

		case CQuestPopup::QuestProgress::QUESTFIVE:
		{
			auto playerPos = _playerPos;
			auto pos = D3DXVECTOR3(375.0f, 0.0f, -305.0f);
			pos.y = GET_MAP("FieldMap")->getHeightMapY(pos) + 1.0f;
			auto delta = playerPos - pos;
			if (D3DXVec3Length(&delta) <= 3.0f)
			{
				// 포탈이랑 거리가 50밑
				ended = true;
			}
			break;
		}

		case CQuestPopup::QuestProgress::QUESTFINAL:
		{

			sprintf(_questString, "\n%d.고룡 베르고스 사냥하기. \n\n   고룡 베르고스 처치!!! ", (int)_questProgress,
				CREATE_MAX_VERGOS - _monsterCount[7], MAX_VERGOS);

			if ((CREATE_MAX_VERGOS - _monsterCount[7]) >= MAX_VERGOS)
			{
				printf("베르고스야!!!!!!!!!! 넌 내꺼야!!!!!!!!!!!!!!!!");
			}

			_progressLabel->setString(_questString);

			break;
		}
		case CQuestPopup::QuestProgress::NONE:
		{

			break;
		}
		default:
		{

			break;
		}
		}
	}


	


}




