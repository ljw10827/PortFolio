#include "BossScene.h"
#include "../Map/bossRoom.h"
#include "../Map/CTeraMapManager.h"
#include "../../Global/Utility/Object/CSkinnedMeshBoss.h"
#include "../Monster/CMonsterFactory.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../Monster/MBasilisk.h"

void BossScene::init(void)
{
	CSceneObject::init();
	_completeInitCount = 0;
	_isInitScene = false;
	_initStep = EInitStep::STEP01;
	_sceneName = "BossScene";
}

void BossScene::update(void)
{
	CSceneObject::update();
	_isUpdateEnd = false;


	if (!_isInitScene) {

		switch (_initStep)
		{
			case CSceneObject::EInitStep::STEP01: {
				_map = new bossRoom();
				_map->init();
				this->addChildObject(_map);
				GET_MAP_MANAGER()->addTeraMap("BossMap", _map);
				_completeInitCount += 17;
				break;
			}
			case CSceneObject::EInitStep::STEP02: {
				_teraUI = new CTeraUI(CTeraUI::EMapKind::bossMap);
				_teraUI->init();
				this->addChildObject(_teraUI);
				_teraUI->settingBossHpVisible();
				_completeInitCount += 5;
				break;
			}
			case CSceneObject::EInitStep::STEP03: {
				_player = new CPlayer();
				_player->init();
				this->addChildObject(_player);
				_player->setPosition(D3DXVECTOR3(-200, 0, 0.0f));
				_player->setRotation(D3DXVECTOR3(0, 90.0f, 0));
				_completeInitCount += 15;
				break;
			}
			case CSceneObject::EInitStep::STEP04: {
				GET_MONSTER()->CreateVergos();
				_completeInitCount += 25;
				break;
			}
			case CSceneObject::EInitStep::STEP05: {

				for (auto monster : GET_MONSTER()->getAllMonsterList()) {
					if (monster->getMonsterName() == "M_Vergos") this->addChildObject((MPollutedWolf*)monster);
				}

				_completeInitCount += 25;
				_isInitScene = true;
				break;
			}
		}

		_initCount++;
		_initStep = (EInitStep)_initCount;
	}
	else {

		if (!_isPlayingBGM) {
			_isPlayingBGM = true;
			PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/NewBattle_02.wav");
		}

		// 보스와 첫전투가 시작되면 음악을 변경한다.
		// 첫전투 지점에서 TRUE 해주어야함.
		if (_isStartBattle) {
			_isStartBattle = false;
			PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_1.wav");
			this->BossSoundTrack();
		}

		//! 카메라 거리 조절
		_cameraFar += GET_MOUSE_WHEEL() / 30.f;
		GET_CAMERA()->setFollowObject(_player, D3DXVECTOR3(0.0f, 0.0f, _cameraFar), EFollowType::FREE);


		// 미니맵의 플레이어 포지션 갱신
		_teraUI->setPlayerPosition(_player->getPosition().x, _player->getPosition().z);
		// }

		// 몬스터 y값 조절
		// {

		// }

		

		// 임시 바운딩 스피어조절
		if (IS_KEY_PRESSED(DIK_F1)) {
			if (_player->getSkinnedMesh()->getDebugEnable())
				_player->getSkinnedMesh()->setDebugEnable(false);
			else
				_player->getSkinnedMesh()->setDebugEnable(true, EDebugType::SPHERE);
		}
		else if (IS_KEY_PRESSED(DIK_F2)) {
			for (auto monster : GET_MONSTER()->getAllMonsterList()) {
				if (monster->getSkinnedMeshBoss()->getDebugEnable())
					monster->getSkinnedMeshBoss()->setDebugEnable(false);
				else
					monster->getSkinnedMeshBoss()->setDebugEnable(true, EDebugType::SPHERE);
			}
		}

		// 씬전환 키
		if (IS_KEY_PRESSED(DIK_RCONTROL)) {
			_isKilledBoss = true;
		}

		_isUpdateEnd = true;

		// 씬전환 되는 시점
		// 보스가 죽엇을경우.
		if (_isKilledBoss && _isDrawEnd && _isDrawUIEnd && _isUpdateEnd) {
			// TODO : 엔딩
			printf("끝@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("끝@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("끝@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			printf("끝@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		}
	}
}

void BossScene::BossSoundTrack(void)
{
	SET_SCHEDULE(132, [=](void)->void {
		PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_2.wav");

		SET_SCHEDULE(132, [=](void)->void {
			PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_3.wav");

			SET_SCHEDULE(137, [=](void)->void {
				PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_4.wav");

				SET_SCHEDULE(137, [=](void)->void {
					PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_5.wav");

					SET_SCHEDULE(137, [=](void)->void {
						PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_6.wav");

						SET_SCHEDULE(127, [=](void)->void {
							PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_7.wav");

							SET_SCHEDULE(126, [=](void)->void {
								PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Boss/Boss_Battle_8.wav");

							});
						});
					});
				});
			});
		});
	});
}
