#include "CNPC.h"
#include "../../Global/Utility/Object/CSkinnedMesh.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "../../Global/Utility/Object/CCamera.h"
#include "../../Global/Utility/Base/CWindowApplication.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../../Tera/Monster/CMonsterFactory.h"
#include "../Monster/MBasilisk.h"
#include "../Map/CTeraMapManager.h"

CNPC::CNPC(const std::string & npcName)
	:
	_name(npcName)
{
	ZeroMemory(_direction, sizeof(D3DXVECTOR3));
}

CNPC::~CNPC(void)
{
	SAFE_DELETE(_skinnedMesh);
}

void CNPC::init(void)
{
	// 최초 방향체인지 시간
	_changeDirTime = CreateFloatRandomValue(10.0f, 20.0f);
	_changeAnimTime = CreateFloatRandomValue(5.0f, 15.0f);

	// 초기화
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 30.0f, 0.01f, 30.0f);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);
	
	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;

	_skinnedMesh = this->CreateSkinnedMesh();

	_skinnedMesh->setScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	_skinnedMesh->setRotation(D3DXVECTOR3(0.0f, -90.0f, 0.0f));
	_skinnedMesh->setShadowEnable(true);
	_skinnedMesh->setShadowMatrix(worldMatrix);
	_skinnedMesh->setDebugEnable(true, EDebugType::SPHERE);
	_skinnedMesh->setTimeScale(0.8f);
	this->addChildObject(_skinnedMesh);

	

}

void CNPC::update(void)
{
	CRenderObject::update();
	
	auto pos = this->getPosition();
	pos.y = ((filedMap*)GET_MAP(GET_MAP_MANAGER()->getName()))->getHeightMapY(pos);
	this->setPosition(pos);

	//방향
	if (_changeDirTimer >= _changeDirTime) {
		_changeDirTime = CreateFloatRandomValue(10.0f, 20.0f);
		this->Move();
	}
	else {
		// 방향 바꿀 타임 랜덤 정하기
		_changeDirTimer += GET_DELTA_TIME();
	}

	// 애니메이션
	if (_changeAnimTimer >= _changeAnimTime) {
		_changeAnimTime = CreateFloatRandomValue(5.0f, 15.0f);
		this->Animation();
	}
	else {
		// 방향 바꿀 타임 랜덤 정하기
		_changeAnimTimer += GET_DELTA_TIME();
	}


	if (IS_MOUSE_PRESSED((int)EMouseInput::LEFT_BUTTON)) {
		auto mousePos = GET_MOUSE_POSITION();
		STRay stRay = CreateRay(mousePos);

		printf("%d, %d \n", mousePos.x, mousePos.y);

		auto boundingSphere = _skinnedMesh->getFinalBoundingSphere();

		if (IsIntersectRaySphere(stRay, boundingSphere)) {
			printf("충돌\n");
		}
		else {
			printf("놉\n");
		}
	}

}

void CNPC::Move(void)
{
	_changeDirTimer = 0.0f;

	// 랜덤 방향을 정한다.
	_direction.x = CreateFloatRandomValue(-1.0000f, 1.0000f);
	_direction.z = CreateFloatRandomValue(-1.0000f, 1.0000f);

	D3DXVec3Normalize(&_direction, &_direction);

}

void CNPC::Animation(void)
{
	_changeAnimTimer = 0.0f;

	//랜덤 애니메이션을 정한다
	auto animNameList = _skinnedMesh->getAnimationNameList();
	int animNum = CreateIntRandomValue(0, animNameList.size() - 1);
	
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

	if (_name == "NPC_Castanic_G01")
	{
		skinnedType = SkinnedType::NCastanic;
	}

	return new CSkinnedMesh(parameters, skinnedType);
}
