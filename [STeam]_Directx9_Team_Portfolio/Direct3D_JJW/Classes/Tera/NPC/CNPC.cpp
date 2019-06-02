#include "CNPC.h"
#include "../../Global/Utility/Object/CSkinnedMesh.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "../../Global/Utility/Object/CCamera.h"
#include "../../Global/Utility/Base/CWindowApplication.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../../Tera/Monster/CMonsterFactory.h"
#include "../Monster/MBasilisk.h"
#include "../Map/CTeraMapManager.h"
#include "../TeraScene/MainScene.h"
#include "../../Global/Utility/UI/CSprite.h"
#include "../../Global/Utility/Manager/CResourceManager.h"
#include "../../Tera/TeraUI/CQuestPopup.h"

CNPC::CNPC(const std::string & npcName)
	:
	_name(npcName)
{
	ZeroMemory(_direction, sizeof(D3DXVECTOR3));
	ZeroMemory(_playerPosition, sizeof(D3DXVECTOR3));
}

CNPC::~CNPC(void)
{
	SAFE_DELETE(_skinnedMesh);
}



void CNPC::init(void)
{
	// 최초 방향체인지 시간
	_changeDirTime = CreateFloatRandomValue(10.0f, 20.0f);
	_changeAnimTime = CreateFloatRandomValue(5.0f, 25.0f);

	// 각종 값 초기화
	_moveSpeed = CreateFloatRandomValue(2.0f, 4.0f);
	_moveTime = CreateFloatRandomValue(0.5f, 2.0f);

	// 초기화
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 20.0f, 0.01f, 20.0f);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);
	
	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;

	_skinnedMesh = this->CreateSkinnedMesh();

	_skinnedMesh->setScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	if (_name != "NPC_General_M01") {
		_skinnedMesh->setRotation(D3DXVECTOR3(0.0f, 45.0f, 0.0f));
	}
	
	_skinnedMesh->setShadowEnable(true);
	_skinnedMesh->setShadowMatrix(worldMatrix);
	//_skinnedMesh->setDebugEnable(true, EDebugType::SPHERE);
	_skinnedMesh->setTimeScale(0.8f);

	this->addChildObject(_skinnedMesh);

	if (_name == "NPC_Rabbit" || _name == "NPC_Sheep" || _name == "NPC_SheepNaked" || _name == "NPC_SmallDog") {
		_npcKind = ENpcKind::ANIMAL;
	}
	else if (_name == "NPC_Barricade") {
		_npcKind = ENpcKind::NONE;
	}
	else {
		_npcKind = ENpcKind::NPC;
	}

	// 사운드를 넣어서 사운드 재생을 좀 빠르게하여 진입부분에서 들리게하려햇는데
	// 사운드가 없음 경비병
	/*if (_name == "NPC_Soldier_M01" || _name == "NPC_Soldier_M02") {
		_changeAnimTime = CreateFloatRandomValue(4.0f, 4.0f);
	}*/

	if (_name == "NPC_Castanic_G01" ) {
		_changeAnimTime = CreateFloatRandomValue(6.0f, 6.0f);
	}

	
}

void CNPC::update(void)
{
	CRenderObject::update();
	


	auto pos = this->getPosition();
	pos.y = GET_MAP("FieldMap")->getHeightMapY(pos)+1.0f;
	this->setPosition(pos);

	//  동물만 회전
	if (_npcKind == ENpcKind::ANIMAL) {
		if(_isMoveAnimal) {
			_moveTimer += GET_DELTA_TIME();

			this->rotateByDirection(_direction);

			if (_direction.x < 0) {
				this->moveByXAxis(_direction.x * -1.0f * _moveSpeed * GET_DELTA_TIME());
			}
			else if (_direction.x >= 0) {
				this->moveByXAxis(_direction.x * _moveSpeed * GET_DELTA_TIME());
			}

			if (_moveTimer >= _moveTime) {
				_changeDirTimer = 0.0f;
				_isMoveAnimal = false;
				

				auto animNameList = _skinnedMesh->getAnimationNameList();
				int animNum = CreateIntRandomValue(0, animNameList.size() - 1);

				// 워크라는 애니메이션이 걸리면 다시 찾는다.
				while (animNameList[animNum] == "Walk" || animNameList[animNum] == "Run") {
					animNum = CreateIntRandomValue(0, animNameList.size() - 1);
				}

				if (animNameList[animNum] == "Wait") {
					_skinnedMesh->PlayAnimation(animNameList[animNum], true);
				}

				else {
					_skinnedMesh->PlayAnimation(animNameList[animNum], false, false, [=](const std::string &animName)->void {
						_skinnedMesh->PlayAnimation("Wait", true);
					});
				}
			}
		}
		else {
			_changeDirTimer += GET_DELTA_TIME();

			// 노말상태에서 방향타이머가 해당시간을 넘어가면 랜덤 방향으로 이동하라
			if (_changeDirTimer >= _changeDirTime) {
				this->Move();
			}
		}
	}
	else if (_npcKind == ENpcKind::NPC) {
		// 애니메이션
		if (_changeAnimTimer >= _changeAnimTime) {
			_changeAnimTime = CreateFloatRandomValue(5.0f, 15.0f);
			this->Animation();
		}
		else {
			// 애니 바꿀 타임 랜덤 정하기
			_changeAnimTimer += GET_DELTA_TIME();
		}
	}

	auto ray = CreateRay(GET_MOUSE_POSITION());

	if (_name == "NPC_General_M01"
		&& IsIntersectRaySphere(ray, _skinnedMesh->getFinalBoundingSphere())
		&& GET_DIRECT3D_APPLICATION()->getPressedLCtrl())
	{
		SetCursor(LoadCursorFromFileA("Resources/Cursor/action.ani"));

		if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON))
		{
			auto boundingSphere = _skinnedMesh->getFinalBoundingSphere();

			_playerPosition = ((MainScene*)(this->m_pParentObject))->getPlayerPosition();
			auto delta = this->getPosition() - _playerPosition;
			auto npcDirection = _playerPosition - this->getPosition();

			_skinnedMesh->setDebugEnable(false);

			auto distance = D3DXVec3Length(&delta);

			if (distance < 100)
			{
				PLAY_EFFECT_SOUND("Resources/Sounds/NPC/NPC_General_M01/idle07.wav");
				D3DXVec3Normalize(&npcDirection, &npcDirection);
				
				this->rotateByDirection(npcDirection);
				this->rotateByYAxis(-90.0f);
				if (!((MainScene*)(this->m_pParentObject))->getTeraUI()->getQuestPopup()->getisAccept())
				{
					((MainScene*)(this->m_pParentObject))->getTeraUI()->getQuestPopup()->getNpcQuestSprite()->setVisible(true);
				}
			}
			SetCursor(LoadCursorFromFileA("Resources/Cursor/Arrow.cur"));
		}
	}

	((MainScene*)(this->m_pParentObject))->getTeraUI()->getQuestPopup()->setPos(((MainScene*)(this->m_pParentObject))->getPlayerPosition());
}

void CNPC::Move()
{
	_isMoveAnimal = true;
	_moveTimer = 0.0f;

	// 랜덤 방향을 정한다.
	_direction.x = CreateFloatRandomValue(-1.0000f, 1.0000f);
	_direction.z = CreateFloatRandomValue(-1.0000f, 1.0000f);

	D3DXVec3Normalize(&_direction, &_direction);

	if (_name == "NPC_Sheep" || _name == "NPC_SheepNaked") {
		int choice = CreateIntRandomValue(0, 100);

		if (choice <= 80) _skinnedMesh->PlayAnimation("Walk", true);
		else _skinnedMesh->PlayAnimation("Run", true);
	}
	else {
		// 걷는다.
		_skinnedMesh->PlayAnimation("Walk", true);
	}

	auto playerPos = ((MainScene*)(this->m_pParentObject))->getPlayer()->getPosition();
	auto dir = playerPos - this->getPosition();
	auto distance = D3DXVec3Length(&dir);

	if (distance < 40) {
		char animName[16] = "";
		sprintf(animName, "Wait%02d", CreateIntRandomValue(1, 3));
		PLAY_EFFECT_SOUND("Resources/Sounds/NPC/NPC_Sheep/" + (std::string)animName + ".wav");
	}
}

void CNPC::Animation(void)
{
	_changeAnimTimer = 0.0f;

	// 동물이 이동중이 아닐때만(NPC라면 해당사항없으므로 무조건들어옴)
	if (!_isMoveAnimal) {

		//랜덤 애니메이션을 정한다
		auto animNameList = _skinnedMesh->getAnimationNameList();
		int animNum = CreateIntRandomValue(0, animNameList.size() - 1);

		// 워크라는 애니메이션이 걸리면 다시 찾는다.
		while (animNameList[animNum] == "walk") {
			animNum = CreateIntRandomValue(0, animNameList.size() - 1);
		}

		if (animNameList[animNum] == "wait") {
			_skinnedMesh->PlayAnimation(animNameList[animNum], true);
		}
		else {
			_skinnedMesh->PlayAnimation(animNameList[animNum], false, false, [=](const std::string &animName)->void {
				_skinnedMesh->PlayAnimation("wait", true);
			});
		}

		// 사운드 잠시보류
		// 사운드 볼륨조절
		auto playerPos = ((MainScene*)(this->m_pParentObject))->getPlayer()->getPosition();
		auto dir = playerPos - this->getPosition();
		auto distance = D3DXVec3Length(&dir);

		if (distance < 50) {
			char animName[16] ="";

			if (_name == "NPC_Castanic_G01") {
				if (animNameList[animNum] == "idle") {
					sprintf(animName, "%s%02d", animNameList[animNum].c_str(), CreateIntRandomValue(1, 10));
					PLAY_EFFECT_SOUND("Resources/Sounds/NPC/NPC_Castanic_G01/" + (std::string)animName + ".wav");
				}
			}

			/*if (_name == "NPC_Soldier_M01") {
				if (animNameList[animNum] == "idle") {
					sprintf(animName, "%s%02d", animNameList[animNum].c_str(), CreateIntRandomValue(1, 8));
					PLAY_EFFECT_SOUND("Resources/Sounds/NPC/NPC_Soldier_M01/" + (std::string)animName + ".wav");
				}
			}

			if (_name == "NPC_Soldier_M02") {
				if (animNameList[animNum] == "idle") {
					sprintf(animName, "%s%02d", animNameList[animNum].c_str(), CreateIntRandomValue(1, 8));
					PLAY_EFFECT_SOUND("Resources/Sounds/NPC/NPC_General_M01/" + (std::string)animName + ".wav");
				}
			}*/
		}
	}
}


CSkinnedMesh * CNPC::CreateSkinnedMesh(void)
{
	std::string npcName = _name + "/" + _name + ".x";

	CSkinnedMesh::STParameters parameters = {
		"Resources/Meshes/NPC/" + npcName,
		"Resources/Effects/NPCEffect.fx",
		"Dummy_root",
		"none",
		"none",
		"none"
	};

	SkinnedType skinnedType;

	if (_name == "NPC_Castanic_G01") skinnedType = SkinnedType::NCastanic;
	else if (_name == "NPC_General_M01") skinnedType = SkinnedType::NGeneral;
	else if (_name == "NPC_Human_F01") skinnedType = SkinnedType::NHumanF;
	else if (_name == "NPC_Rabbit") skinnedType = SkinnedType::NRabbit;
	else if (_name == "NPC_Sheep") skinnedType = SkinnedType::NSheep;
	else if (_name == "NPC_SmallDog") skinnedType = SkinnedType::NDog;
	else if (_name == "NPC_SheepNaked") skinnedType = SkinnedType::NSheepNaked;
	else if (_name == "NPC_Soldier_M01") skinnedType = SkinnedType::NSoldier01;
	else if (_name == "NPC_Soldier_M02") skinnedType = SkinnedType::NSoldier02;
	else if (_name == "NPC_Barricade") skinnedType = SkinnedType::NBarricade;

	return new CSkinnedMesh(parameters, skinnedType);
}
