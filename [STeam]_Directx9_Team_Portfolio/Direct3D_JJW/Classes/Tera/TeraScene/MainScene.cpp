#include "MainScene.h"
#include "../Monster/CMonsterFactory.h"
#include "../Map/filedMap.h"
#include "../Map/CTeraMapManager.h"
#include "../NPC/CNPC.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../../Global/Utility/Sound/CSound.h"
#include "LoadingScene.h"
#include "../TeraUI/CQuestPopup.h"
MainScene::MainScene(void)
{
}

MainScene::~MainScene(void)
{
	CSceneObject::~CSceneObject();
}

void MainScene::init(void)
{
	CSceneObject::init();
	_isInitScene = false;
	_initStep = EInitStep::STEP01;
	_sceneName = "MainScene";
	
}

void MainScene::update(void)
{
	CSceneObject::update();
	_isUpdateEnd = false;

	if (!_isInitScene) {

		// -------------------------------------- 실제 초기화 ---------------------------------------///
		// {
		switch (_initStep)
		{
			case MainScene::EInitStep::STEP01: {
				_map = new filedMap();
				_map->init();
				this->addChildObject(_map);
				GET_MAP_MANAGER()->addTeraMap("FieldMap", _map);
				_completeInitCount += 10.0f;
				break;
			}
			case MainScene::EInitStep::STEP02: {
				_player = new CPlayer();
				_player->init();
				this->addChildObject(_player);
				_player->setPosition(D3DXVECTOR3(-206.0f, -34.0f, -49.0f));
				GET_CAMERA()->setFollowObjectEnable(true);
				_completeInitCount += 5.0f;
				break;
			}
			case MainScene::EInitStep::STEP03: {
				GET_MONSTER()->CreateBasilisk(CREATE_MAX_BASILISK);
				_completeInitCount += 5.0f;
				break;
			}
			
			case MainScene::EInitStep::STEP04: {
				GET_MONSTER()->CreateArgass(CREATE_MAX_ARGASS);
				_completeInitCount += 3.0f;
				break;
			}
			
			case MainScene::EInitStep::STEP05: {
				GET_MONSTER()->CreateCraftySpider(CREATE_MAX_CRAFTYSPIDER);
				_completeInitCount += 5.0f;
				break;
			}
			
			case MainScene::EInitStep::STEP06: {
				GET_MONSTER()->CreateDooBean(CREATE_MAX_DOOBEAN);
				_completeInitCount += 2.0f;
				break;
			}
			
			case MainScene::EInitStep::STEP07: {
				GET_MONSTER()->CreateGhillieDhu(CREATE_MAX_GHILLIEDHU);
				_completeInitCount += 3.0f;
				break;
			}
			
			case MainScene::EInitStep::STEP08: {
				GET_MONSTER()->CreatePlantMini(CREATE_MAX_PLANT);
				_completeInitCount += 2.0f;
				break;
			}
			
			case MainScene::EInitStep::STEP09: {
				GET_MONSTER()->CreatePollutedWolf(CREATE_MAX_POLLUTEDWOLF);
				_completeInitCount += 5.0f;
				break;
			}
			case MainScene::EInitStep::STEP10: {
				for (auto monster : GET_MONSTER()->getAllMonsterList()) {
					if (monster->getMonsterName() == "M_Argass") this->addChildObject((MArgass*)monster);
					if (monster->getMonsterName() == "M_Basilisk") this->addChildObject((MBasilisk*)monster);
					if (monster->getMonsterName() == "M_CraftySpider") this->addChildObject((MCraftySpider*)monster);
					if (monster->getMonsterName() == "M_DooBean") this->addChildObject((MDooBean*)monster);
					if (monster->getMonsterName() == "M_GhillieDhu") this->addChildObject((MGhillieDhu*)monster);
					if (monster->getMonsterName() == "M_Plant_mini") this->addChildObject((MPlantMini*)monster);
					if (monster->getMonsterName() == "M_PollutedWolf") this->addChildObject((MPollutedWolf*)monster);
				}
				_completeInitCount += 7.0f;
				break;
			}
			case MainScene::EInitStep::STEP11: {
				_teraUI = new CTeraUI(CTeraUI::EMapKind::mainMap);
				_teraUI->init();
				this->addChildObject(_teraUI);
				_completeInitCount += 2.0f;
				break;
			}
			case MainScene::EInitStep::STEP12: {

				break;
			}
			case MainScene::EInitStep::STEP13: {
				auto girl = new CNPC("NPC_Castanic_G01");
				girl->init();
				girl->setPosition(D3DXVECTOR3(-371, 0.0f, 122));
				girl->rotateByYAxis(45);
				this->addChildObject(girl);
				_completeInitCount += 2.0f;
				break;
			}
			case MainScene::EInitStep::STEP14: {
				auto general = new CNPC("NPC_General_M01");
				general->init();
				general->setPosition(D3DXVECTOR3(-338, 0.0f, 154.f));
				general->rotateByYAxis(135);
				this->addChildObject(general);
				_completeInitCount += 2.0f;
				break;
			}
			case MainScene::EInitStep::STEP15: {
				auto hWoman = new CNPC("NPC_Human_F01");
				hWoman->init();
				hWoman->setPosition(D3DXVECTOR3(-253, 0.0f, 97.f));
				hWoman->rotateByYAxis(-180);
				this->addChildObject(hWoman);
				_completeInitCount += 2.0f;
				break;
			}
			case MainScene::EInitStep::STEP16: {
				auto soldier01 = new CNPC("NPC_Soldier_M01");
				soldier01->init();
				soldier01->setPosition(D3DXVECTOR3(-233, 0.0f, -69));
				this->addChildObject(soldier01);
				_completeInitCount += 2.0f;
				break;
			}
			case MainScene::EInitStep::STEP17: {
				auto soldier02 = new CNPC("NPC_Soldier_M02");
				soldier02->init();
				soldier02->setPosition(D3DXVECTOR3(-208, 0.0f, -24));
				soldier02->rotateByYAxis(45);
				this->addChildObject(soldier02);
				_completeInitCount += 2.0f;
				break;
			}
			case MainScene::EInitStep::STEP18: {
				for (int i = 0; i < 20; ++i) {
					auto rabbit = new CNPC("NPC_Rabbit");
					rabbit->init();
					rabbit->setPosition(D3DXVECTOR3(
						CreateIntRandomValue(-300, 300),
						0.0f,
						CreateIntRandomValue(-300, 300)));
					rabbit->rotateByYAxis(CreateIntRandomValue(0, 180));
					this->addChildObject(rabbit);
				}
				_completeInitCount += 7.0f; 
				break;
			}

			case MainScene::EInitStep::STEP19: {
				for (int i = 0; i < 3; ++i) {
					auto sheep = new CNPC("NPC_Sheep");
					sheep->init();
					sheep->setPosition(D3DXVECTOR3(
						-270 + CreateIntRandomValue(-120, 120),
						0.0f,
						-20.0f + CreateIntRandomValue(-60, 60)));
					sheep->rotateByYAxis(CreateIntRandomValue(0, 180));
					this->addChildObject(sheep);
				}
				_completeInitCount += 2.0f;
				break;
			}

			case MainScene::EInitStep::STEP20: {
				for (int i = 0; i < 3; ++i) {
					auto sheep = new CNPC("NPC_SheepNaked");
					sheep->init();
					sheep->setPosition(D3DXVECTOR3(
						-270 + CreateIntRandomValue(-60, 60),
						0.0f,
						-20.0f + CreateIntRandomValue(-120, 120)));
					sheep->rotateByYAxis(CreateIntRandomValue(0, 180));
					this->addChildObject(sheep);
				}
				_completeInitCount += 2.0f;
				break;
			}

			case MainScene::EInitStep::STEP21: {
				for (int i = 0; i < 6; ++i) {
					auto dog = new CNPC("NPC_SmallDog");
					dog->init();
					dog->setPosition(D3DXVECTOR3(
						-170 + CreateIntRandomValue(-100, 100),
						0.0f,
						-20.0f + CreateIntRandomValue(-120, 120)));
					dog->rotateByYAxis(CreateIntRandomValue(0, 180));
					this->addChildObject(dog);
				}
				_completeInitCount += 2.0f;
				break;
			}

			case MainScene::EInitStep::STEP22: {
				auto bari = new CNPC("NPC_Barricade");
				bari->init();
				bari->setPosition(D3DXVECTOR3(-200, -33, -8));
				bari->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari);

				auto bari2 = new CNPC("NPC_Barricade");
				bari2->init();
				bari2->setPosition(D3DXVECTOR3(-204, -33, -19));
				bari2->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari2);

				auto bari3 = new CNPC("NPC_Barricade");
				bari3->init();
				bari3->setPosition(D3DXVECTOR3(-190, -33, -12));
				bari3->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari3);

				auto bari4 = new CNPC("NPC_Barricade");
				bari4->init();
				bari4->setPosition(D3DXVECTOR3(-194, -33, -23));
				bari4->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari4);

				_completeInitCount += 2.0f;
				break;
			}

			case MainScene::EInitStep::STEP23: {
				auto bari = new CNPC("NPC_Barricade");
				bari->init();
				bari->setPosition(D3DXVECTOR3(-208, -33, -78));
				bari->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari);

				auto bari2 = new CNPC("NPC_Barricade");
				bari2->init();
				bari2->setPosition(D3DXVECTOR3(-212, -33, -89));
				bari2->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari2);

				auto bari3 = new CNPC("NPC_Barricade");
				bari3->init();
				bari3->setPosition(D3DXVECTOR3(-218, -33, -72));
				bari3->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari3);

				auto bari4 = new CNPC("NPC_Barricade");
				bari4->init();
				bari4->setPosition(D3DXVECTOR3(-222, -33, -83));
				bari4->setRotation(D3DXVECTOR3(0, 155, 0));
				this->addChildObject(bari4);
				_completeInitCount += 2.0f;
				break;
			}
			case MainScene::EInitStep::STEP24: {
				_portal = new CTeraEffect(L"Resources/Effekseers/Portal3.efk");
				_portal->setDeltaTime(0.05f);
				this->addChildObject(_portal);

				_completeInitCount += 4.0f;
				_isInitScene = true;
				break;
			}
		}

		_initCount++;
		_initStep = (EInitStep)_initCount;
		// }
		// ------------------------------------------------------- 초기화 끝 
	}
	else {
		if (!_isPlayingBGM) {
			_isPlayingBGM = true;
			PLAY_BACKGROUND_SOUND("Resources/Sounds/Music/BGM/Main/Beginner_Village.wav");
		}

		_subBGMTimer += GET_DELTA_TIME();
		if (_subBGMTimer >= CreateFloatRandomValue(10.0f, 20.0f)) {
			int random = CreateIntRandomValue(0, 6);

			switch (random) {
			case 0:
				PLAY_EFFECT_SOUND("Resources/Sounds/Music/subBGM/Ambient_Forest_00.wav");
				break;
			case 1:
				PLAY_EFFECT_SOUND("Resources/Sounds/Music/subBGM/Ambient_Forest_01.wav");
				break;
			case 2:
				PLAY_EFFECT_SOUND("Resources/Sounds/Music/subBGM/Ambient_Forest_02.wav");
				break;
			case 3:
				PLAY_EFFECT_SOUND("Resources/Sounds/Music/subBGM/Ambient_Forest_03.wav");
				break;
			case 4:
				PLAY_EFFECT_SOUND("Resources/Sounds/Music/subBGM/Ambient_Forest_04.wav");
				break;
			case 5:
				PLAY_EFFECT_SOUND("Resources/Sounds/Music/subBGM/Ambient_Forest_05.wav");
				break;
			}
			_subBGMTimer = 0.0f;
		}

		//임시 사운드조절
		if (IS_KEY_DOWN(DIK_UP)) {
			_volume += 1.0f * GET_DELTA_TIME();
		}
		else if (IS_KEY_DOWN(DIK_DOWN)) {
			_volume -= 1.0f * GET_DELTA_TIME();
		}

		_volume = max(0.0f, _volume);
		_volume = min(1.0f, _volume);

		GET_SOUND_MANAGER()->setBGSoundVolume(_volume);
		GET_SOUND_MANAGER()->setEffectsVolume(_volume);

		if (IS_KEY_PRESSED(DIK_HOME)) {
			GET_SOUND_MANAGER()->PauseBGSound();
		}

		if (IS_KEY_PRESSED(DIK_END)) {
			GET_SOUND_MANAGER()->StopBGSound();
		}


		//! 카메라 거리 조절
		_cameraFar += GET_MOUSE_WHEEL() / 30.f;
		GET_CAMERA()->setFollowObject(_player->getSkinnedMesh(), D3DXVECTOR3(0.0f, 0.0f, _cameraFar), EFollowType::FREE);

		//! 카메라 y축 보정
		if (_cameraFar > -7) {
			_cameraFar = -7;
		}

		GET_CAMERA()->setFollowObject(_player->getSkinnedMesh(), D3DXVECTOR3(0.0f, 0.0f, _cameraFar), EFollowType::FREE);

		auto stCameraPosition = GET_CAMERA()->getPosition();

		GET_CAMERA()->setMapHeightPositionYIsBool(false);

		if (stCameraPosition.y <= ((filedMap*)GET_MAP("FieldMap"))->getHeightMapY(stCameraPosition) + 11 &&
			GET_INPUT_MANAGER()->getNowMousePosition().y - GET_INPUT_MANAGER()->getPrevMousePosition().y < 0)
		{
			GET_CAMERA()->setMapHeightPositionYIsBool(true);
			GET_CAMERA()->setMapHeightPositionY(((filedMap*)GET_MAP("FieldMap"))->getHeightMapY(stCameraPosition) + 10.0f);
			GET_CAMERA()->setFollowObject(_player->getSkinnedMesh(), D3DXVECTOR3(0.0f, 0.0f, _cameraFar), EFollowType::FREE);
		}

		// 미니맵의 플레이어 포지션 갱신
		_teraUI->setPlayerPosition(_player->getPosition().x, _player->getPosition().z);

		// 레이더에대한 몬스터 포지션 갱신
		for (auto monster : GET_MONSTER()->getAllMonsterList()) {
			_teraUI->setMonsterPosition(monster->getPosition());
		}


		//// 충돌 처리 - 전체 몬스터
		//auto pSphere = _player->getSkinnedMesh()->getFinalMainWeaponBoundingSphereW();
		//auto pSphere2 = _player->getSkinnedMesh()->getFinalSubWeaponBoundingSphereW();
		//auto monsterList = GET_MONSTER()->getAllMonsterList();


		//_hitCount += GET_DELTA_TIME();

		//// 플레이어 -> 몬스터 공격 판정
		//// 플레이어 공격이 몬스터에 닿았는가?
		//for (auto &monster : monsterList) {
		//	auto mSphere = monster->getSkinnedMesh()->getFinalBoundingSphere();

		//	if (isIntersectSphere(pSphere, mSphere) ||
		//		isIntersectSphere(pSphere2, mSphere)) {
		//		if ((int)(_player->getPlayerState()) == 3) {

		//			monster->BeAttacked(_player, _player->getPlayerStatus().realAtk);
		//		}
		//	}
		//}
		//

		// 스피어 확인용 키
		if (IS_KEY_PRESSED(DIK_F1)) {
			// 플레이어
			if (_player->getSkinnedMesh()->getDebugEnable())
				_player->getSkinnedMesh()->setDebugEnable(false);
			else
				_player->getSkinnedMesh()->setDebugEnable(true, EDebugType::SPHERE);
		}
		else if (IS_KEY_PRESSED(DIK_F2)) {
			//몬스터
			for (auto &monster : GET_MONSTER()->getAllMonsterList()) {
				if (monster->getSkinnedMesh()->getDebugEnable())
					monster->getSkinnedMesh()->setDebugEnable(false);
				else
					monster->getSkinnedMesh()->setDebugEnable(true, EDebugType::SPHERE);
			}
		}
		else if (IS_KEY_PRESSED(DIK_F3)) {
			// 맵 나무
			for (auto &tree : ((filedMap*)_map)->getTreesVector()) {
				tree->getDebugEnable() ? tree->setDebugEnable(false) : tree->setDebugEnable(true, EDebugType::SPHERE);
			}
		}


		// 씬전환 키
		if (IS_KEY_PRESSED(DIK_RCONTROL)) {
			_completedAllQuest = true;
		}

		_isUpdateEnd = true;

		//---------------------- completedAllQuest를 설정해야함. 그래야 보스씬으로 넘어갈수있음.

		if (((CQuestPopup*)_teraUI->getQuestPopup())->getEnded()) {
			_completedAllQuest = true;
		}
		// 씬전환 되는 시점
		if (_completedAllQuest && _isDrawEnd && _isDrawUIEnd && _isUpdateEnd) {
			auto nextScene = new LoadingScene("Boss");
			nextScene->init();
			GET_MONSTER()->RemoveAllMonster();
			GET_SCENE_MANAGER()->replaceSceneObject(nextScene);
		}
	}

}
