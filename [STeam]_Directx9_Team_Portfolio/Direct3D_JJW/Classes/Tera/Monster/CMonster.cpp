#include "CMonster.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../Map/CTeraMapManager.h"
#include "CMonsterFactory.h"
#include "../StaticMesh/CStaticMesh_Map.h"
#include "../TeraScene/MainScene.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "../../Global/Utility/Object/CSkinnedMeshBoss.h"

CMonster::CMonster(const std::string & monsterName)
	:
	_state(EState::NORMAL),
	_monsterName(monsterName)
{
	ZeroMemory(&_status, sizeof(STStatus));
	ZeroMemory(&_direction, sizeof(D3DXVECTOR3));
}

CMonster::~CMonster(void)
{
	SAFE_DELETE(_skinnedMesh);
}

void CMonster::init()
{
	// TODO
	// 스탯 초기값 넣어줘야함.

	// 각종 값 초기화
	_changeDirTime = CreateFloatRandomValue(2.0f, 8.0f);
	_moveTime = CreateFloatRandomValue(1.0f, 3.0f);

	if (_monsterName == "M_Vergos") {
		_skinnedMeshBoss = this->CreateSkinnedMeshBoss();
		_skinnedMeshBoss->setPosition(this->getPosition());
		_skinnedMeshBoss->setScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
		_skinnedMeshBoss->setRotation(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		//_skinnedMesh->setShadowEnable(true);
		//_skinnedMesh->setDebugEnable(true, EDebugType::SPHERE);

		this->addChildObject(_skinnedMeshBoss);
	}
	else {
		_skinnedMesh = this->CreateSkinnedMesh();
		_skinnedMesh->setPosition(this->getPosition());
		_skinnedMesh->setScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
		_skinnedMesh->setRotation(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		//_skinnedMesh->setShadowEnable(true);
		//_skinnedMesh->setDebugEnable(true, EDebugType::SPHERE);

		this->addChildObject(_skinnedMesh);
	}
	

	_damageSkin = new CTeraDMFont();
	this->addChildObject(_damageSkin);


	_criLabel = new CLabel("Critical !!!", 50);
	_criLabel->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f + 150,
		GET_WINDOW_SIZE().cy / 2.0f - 200,
		0.0f));
	_criLabel->rotateByZAxis(20.0f);
	_criLabel->setColor(D3DXCOLOR(0.78f, 0.0f, 0.0f, 0.9f));
	_criLabel->setVisible(false);
	this->addChildObject(_criLabel);

	_missLabel = new CLabel("MISS ..!!!", 40);
	_missLabel->setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f));
	_missLabel->setVisible(false);
	this->addChildObject(_missLabel);
}

void CMonster::update()
{
	CRenderObject::update();

	if (_monsterName != "M_Vergos") {
		// 몬스터의 피가 0이하일경우 (죽엇을경우)
		if (_status.hp <= 0) {
			_state = EState::DEATH;
			_status.hp = 99999;
		}
		else {
			auto position = this->getPosition();
			if ((filedMap*)GET_MAP("FieldMap") != nullptr) {
				position.y = ((filedMap*)GET_MAP("FieldMap"))->getHeightMapY(position) + 1.0f;
				this->setPosition(position);
			}
		}


		//
	// 타겟이 있을 경우에는 전투에 필요한 요소를 계속 계산한다.
		if (_battleObj.target != nullptr) {
			_battleObj.tPos = _battleObj.target->getPosition();
			_battleObj.mPos = this->getPosition();

			_battleObj.tSphere = _battleObj.target->getSkinnedMesh()->getFinalBoundingSphere();
			_battleObj.mWeaponSphere = _skinnedMesh->getFinalMainWeaponBoundingSphereW();
			_battleObj.mSubWeaponSphere = _skinnedMesh->getFinalMainWeaponBoundingSphereW();

			// 실제 몬스터 포지션에서 몸에 크기에 해당하는 스피어의 반지름을 + 해준것.
			_battleObj.mPos.z += _skinnedMesh->getFinalBoundingSphere().radius;
			_battleObj.direction = -1.0f * D3DXVECTOR3(_battleObj.tPos - _battleObj.mPos);
			_battleObj.distance = D3DXVec3Length(&_battleObj.direction);

			//방향 벡터를 따로저장
			D3DXVec3Normalize(&_battleObj.vecDir, &_battleObj.direction);
		}


		switch (_state)
		{
		case CMonster::EState::NONE:
		{
			break;
		}
		case CMonster::EState::MOVE:
		{
			// 방향이 설정되면 여기로들어옴
			auto woodList = ((filedMap*)GET_MAP("FieldMap"))->getTreesVector();

			for (auto &iter : woodList) {
				if (isIntersectSphere(_skinnedMesh->getFinalBoundingSphere(), iter->getFinalBoundingSphere())) {
					this->Move();
				}
			}

			for (auto &iter : GET_MONSTER()->getAllMonsterList()) {
				if (iter == this) continue;
				if (isIntersectSphere(_skinnedMesh->getFinalBoundingSphere(), iter->getFinalBoundingSphere())) {
					this->Move();
				}
			}

			_moveTimer += GET_DELTA_TIME();
			this->rotateByDirection(_direction);

			if (_direction.z < 0) {
				this->moveByZAxis(_direction.z *_moveSpeed * GET_DELTA_TIME());
			}
			else if (_direction.z >= 0) {
				this->moveByZAxis(_direction.z * -1.0f * _moveSpeed * GET_DELTA_TIME());
			}

			if (_moveTimer >= _moveTime) {
				this->Wait();
			}

			break;
		}
		case CMonster::EState::NORMAL:
		{
			_changeDirTimer += GET_DELTA_TIME();
			_soundTimer += GET_DELTA_TIME();
			// 노말상태에서 방향타이머가 해당시간을 넘어가면 랜덤 방향으로 이동하라
			if (_changeDirTimer >= _changeDirTime) {
				this->Move();
			}
			break;
		}
		case CMonster::EState::ATK:
		{
			// 타겟과의 거리가 100 초과 했을때 BeATT으로 전환해서 계쏙따라가게한다
			// 여기서는 타겟과의 거리가 100이하기때문에 공격을 한다.
			// 공격을해서 타겟의 상태를 변화시킨다. 피격함수 호출하여 대미지를 준다
			// 그럼 타겟은 상태 : 비어택드 상태가 된다.

			if (_battleObj.distance < 25) {
				// 공격 랜덤으로 하면됨.
				_isHitAtk = false;
				this->NormalAtk();
			}
			else {
				_state = EState::BEATTACKED;
			}
			break;
		}
		case CMonster::EState::ISATTACKING:
		{
			// 공격하는 모션중에 몬스터의 무기와 충돌이 나면
			if (isIntersectSphere(_battleObj.mWeaponSphere, _battleObj.tSphere)) {
				if (!_isHitAtk) {
					_isHitAtk = true;
					// 최소 ~ 최대 에서 랜덤대미지
					_status.realAtk = CreateIntRandomValue(_status.minAtk, _status.maxAtk);
					_battleObj.target->BeAttacked(this, _status.realAtk);
				}
			}

			break;
		}
		case CMonster::EState::BEATTACKED:
		{
			// 타겟과 거리가 100 이하 일때까지 따라간다
			// 그리고 거리가 100이하면 공격으로 전환한다
			// 100이 넘어가면 어그로 풀림
			if (_battleObj.distance >= 100) {
				_target = nullptr;
				_state = EState::NORMAL;
			}
			// 25 ~ 100사이면 따라감 조금빠른속도로
			else if (_battleObj.distance >= 15) {
				this->rotateByDirection(_battleObj.vecDir);
				this->moveByZAxis(-2.0f * _moveSpeed * GET_DELTA_TIME());
				_skinnedMesh->PlayAnimation("Walk", false);
			}
			// 25보다 작으면 공격하라
			else if (_battleObj.distance < 20.0f) {
				_state = EState::ATK;
			}

			break;
		}
		case CMonster::EState::WALK:
		{
			break;
		}
		case CMonster::EState::DEATH:
		{
			this->Death();
			break;
		}
		case CMonster::EState::REMOVE:
		{
			printf("죽은몬스터 : %s 삭제중\n", _monsterName);
			break;
		}
		}
	}
}

void CMonster::doDrawObject()
{
	CRenderObject::doDrawObject();
}

// ------------------------ 애니메이션 함수

void CMonster::Wait(void)
{
	_state = EState::NORMAL;
	_changeDirTimer = 0.0f;

	_skinnedMesh->PlayAnimation("Wait", true);

	if (_monsterName != "M_DooBean") {
		auto playerPos = ((MainScene*)(this->m_pParentObject))->getPlayer()->getPosition();
		auto dir = playerPos - this->getPosition();
		auto distance = D3DXVec3Length(&dir);

		if (_soundTimer > CreateFloatRandomValue(10.0f, 30.0f)) {
			_soundTimer = 0.0f;
			// 거리가 40 이하라면 재생
			if (distance < 15) {
				char soundName[16] = "";
				sprintf(soundName, "/Wait%02d.wav", CreateIntRandomValue(1, 4));
				PLAY_EFFECT_SOUND("Resources/Sounds/Monster/" + _monsterName + std::string(soundName));
			}
		}
	}
}

void CMonster::Walk()
{
	_state = EState::WALK;

	_skinnedMesh->PlayAnimation("Walk", false, false, [=](const std::string &animName)->void {
		this->Wait();
	});
}

void CMonster::Move()
{
	_state = EState::MOVE;
	_moveTimer = 0.0f;
	
	// 랜덤 방향을 정한다.
	_direction.x = CreateFloatRandomValue(-1.0000f, 1.0000f);
	_direction.z = CreateFloatRandomValue(-1.0000f, 1.0000f);

	D3DXVec3Normalize(&_direction, &_direction);

	// 걷는다.
	_skinnedMesh->PlayAnimation("Walk", true);

	if (_monsterName != "M_DooBean") {
		auto playerPos = ((MainScene*)(this->m_pParentObject))->getPlayer()->getPosition();
		auto dir = playerPos - this->getPosition();
		auto distance = D3DXVec3Length(&dir);

		// 거리가 40 이하라면 재생
		if (distance < 15) {
			char soundName[16] = "";
			sprintf(soundName, "/Walk%02d.wav", CreateIntRandomValue(1, 4));
			PLAY_EFFECT_SOUND("Resources/Sounds/Monster/" + _monsterName + std::string(soundName));
		}
	}
}

void CMonster::NormalAtk()
{
	_state = EState::ISATTACKING;

	// 랜덤 스킬
	_skinnedMesh->PlayAnimation("Atk01", false, false, [=](const std::string &animName)->void {
		_state = EState::ATK;
	});
}

void CMonster::BeAttacked(CPlayer * target, int tDamage)
{
	// 현재 움직이는 중이라면 무브 타이머를 넘겨버려서 움직임을 멈춘다.
	if (_state == EState::MOVE) {
		_moveTimer = 1000;
	}

	char soundName[32] = "";
	sprintf(soundName, "Damage00_%02d.wav", CreateIntRandomValue(0,5));
	PLAY_EFFECT_SOUND("Resources/Sounds/Player/NormalAtk/" + std::string(soundName));

	// 타겟을 지정한다
	_battleObj.target = target; 

	auto tPerAtkCri = target->getPlayerStatus().perAtkCri;
	auto tPerAtkCriDmg = target->getPlayerStatus().perAtkCriDmg;
	auto tAtkAcc = target->getPlayerStatus().perAtkAcc;
	int baseDamage = tDamage;
	bool isCri = false;

	if (tAtkAcc >= CreateIntRandomValue(0, 100)) {
		if (tPerAtkCri >= CreateIntRandomValue(0, 100)) {
			baseDamage = (float)(tDamage * (float)tPerAtkCriDmg / 100.0f);
			isCri = true;
		}

		if (isCri) {
			D3DXVECTOR3 pos = {
				GET_WINDOW_SIZE().cx / 2.0f + CreateFloatRandomValue(-200,200),
				GET_WINDOW_SIZE().cy / 2.0f + CreateFloatRandomValue(-200,100),
				0.0f
			};
			_criLabel->setPosition(pos);
			_criLabel->setVisible(true);

			SET_SCHEDULE(2.0f, [=](void)->void {
				_criLabel->setVisible(false);
			});
		}

		// 대미지계산 후 적용
		auto realDamage = baseDamage * (100 - _status.PerDef) / 100;
		_status.hp -= realDamage;

		auto ranY = 300 + CreateFloatRandomValue(-50, 50);

		_damageSkin->damageCalculate(realDamage, D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f, ranY, 0.0f));

		if (_monsterName != "M_DooBean") {
			auto playerPos = ((MainScene*)(this->m_pParentObject))->getPlayer()->getPosition();
			auto dir = playerPos - this->getPosition();
			auto distance = D3DXVec3Length(&dir);

			// 거리가 40 이하라면 재생
			if (distance < 25) {
				char soundName[16] = "";
				sprintf(soundName, "/Damage.wav");
				PLAY_EFFECT_SOUND("Resources/Sounds/Monster/" + _monsterName + std::string(soundName));
			}
		}

	}
	else { // 미스가 났다면
		D3DXVECTOR3 pos = {
				GET_WINDOW_SIZE().cx / 2.0f + CreateFloatRandomValue(-200,200),
				GET_WINDOW_SIZE().cy / 2.0f + CreateFloatRandomValue(-200,100),
				0.0f
		};
		_missLabel->setPosition(pos);
		// 미스라벨 온 
		_missLabel->setVisible(true);
		// 2초 뒤 오프
		SET_SCHEDULE(2.0f, [=](void)->void {
			_missLabel->setVisible(false);
		});
	}

}

void CMonster::Death()
{
	_state = EState::REMOVE;
	_battleObj.target = nullptr;

	auto playerPos = ((MainScene*)(this->m_pParentObject))->getPlayer()->getPosition();
	auto dir = playerPos - this->getPosition();
	auto distance = D3DXVec3Length(&dir);

	if (_monsterName != "M_DooBean") {
		// 거리가 40 이하라면 재생
		if (distance < 15) {
			char soundName[16] = "";
			sprintf(soundName, "/Death.wav");
			PLAY_EFFECT_SOUND("Resources/Sounds/Monster/" + _monsterName + std::string(soundName));
		}
	}

	_skinnedMesh->PlayAnimation("Death", false, false, [=](const std::string &animName)->void {
		SET_SCHEDULE(3.0f, [=](void)->void {
			this->setVisible(false);
		});
		_skinnedMesh->PlayAnimation("DeathWait", true);
		
	});
}

// ------------------------ private 함수

CSkinnedMesh * CMonster::CreateSkinnedMesh()
{
	std::string monsterName = _monsterName + "/" + _monsterName + ".x";

	std::string mainWeapon = "none";
	std::string subWeapon = "none";
	std::string thirdWeapon = "none";

	SkinnedType skinnedType;

	if (_monsterName == "M_Argass")
	{
		skinnedType = SkinnedType::MArgass;
		mainWeapon = "Bone05";
	}

	else if (_monsterName == "M_Basilisk")
	{
		skinnedType = SkinnedType::MBasilisk;
		mainWeapon = "Bip01-Head";
	}
	
	else if (_monsterName == "M_CraftySpider")
	{
		skinnedType = SkinnedType::MCraftySpider;
		mainWeapon = "FxHand01";
		subWeapon = "FxHand00";
	}
	
	else if (_monsterName == "M_DooBean")
	{
		skinnedType = SkinnedType::MDooBean;
		mainWeapon = "Bone05";
	}
	
	else if (_monsterName == "M_GhillieDhu")
	{
		skinnedType = SkinnedType::MGhillieDhu;
		mainWeapon = "Bip01-R-Hand";
		subWeapon = "Bip01-L-Hand";
	}
	
	else if (_monsterName == "M_Plant_mini")
	{
		skinnedType = SkinnedType::MPlantMini;
		mainWeapon = "Bone25";
	}

	else if (_monsterName == "M_PollutedWolf")
	{
		skinnedType = SkinnedType::MPollutedWolf;
		mainWeapon = "Bip01-Neck1";
	}

	//else if (_monsterName == "M_Vergos")
	//{
	//	skinnedType = SkinnedType::MVergos;
	//	mainWeapon = "Bip01-R-Hand";
	//	subWeapon = "Bip01-L-Hand";
	//	thirdWeapon = "Head_Bone01";
	//}


	CSkinnedMesh::STParameters parameters = {
		"Resources/Meshes/Monster/" + monsterName,
		"Resources/Effects/MonsterEffect.fx",
		"Dummy_root",
		mainWeapon,
		subWeapon,
		thirdWeapon
	};

	//if (_monsterName == "M_Vergos")
	//{
	//	parameters = {
	//		"Resources/Meshes/Monster/" + monsterName,
	//		"Resources/Effects/BossEffect.fx",
	//		"Dummy_root",
	//		mainWeapon,
	//		subWeapon,
	//		thirdWeapon
	//	};
	//}

	return new CSkinnedMesh(parameters, skinnedType);
}

CSkinnedMeshBoss * CMonster::CreateSkinnedMeshBoss()
{
	std::string monsterName = _monsterName + "/" + _monsterName + ".x";

	std::string mainWeapon = "none";
	std::string subWeapon = "none";
	std::string thirdWeapon = "none";

	SkinnedType skinnedType;

	skinnedType = SkinnedType::MVergos;
	mainWeapon = "Bip01-R-Hand";
	subWeapon = "Bip01-L-Hand";
	thirdWeapon = "Head_Bone01";

	CSkinnedMeshBoss::STParameters parameters = {
		"Resources/Meshes/Monster/" + monsterName,
			"Resources/Effects/BossEffect.fx",
			"Dummy_root",
			mainWeapon,
			subWeapon,
			thirdWeapon
	};


	return new CSkinnedMeshBoss(parameters, skinnedType);
}
