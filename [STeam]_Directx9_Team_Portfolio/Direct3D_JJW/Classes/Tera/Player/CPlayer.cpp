#include "CPlayer.h"
#include "../../Global/Utility/Object/CSkinnedMesh.h"
#include "../../Global/Utility/Object/CSkinnedMeshBoss.h"
#include "../../Global/Utility/Manager/CInputManager.h"
#include "../../Global/Utility/Manager/CWindowManager.h"
#include "../../Global/Utility/Manager/CTimeManager.h"
#include "../../Global/Utility/Manager/CSoundManager.h"
#include "../../Global/Utility/Object/CParticleSystem.h"
#include "../../Global/Utility/UI/CLabel.h"
#include "../../Global/Utility/Object/CCamera.h"
#include "../../Global/Utility/Base/CWindowApplication.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../../Tera/Monster/CMonsterFactory.h"
#include "../Monster/MBasilisk.h"
#include "../Map/CTeraMapManager.h"
#include "../Monster/CMonster.h"
#include "../TeraEffect/CTeraEffect.h"
#include "../TeraScene/MainScene.h"
#include "../../Global/Utility/Base/CSceneObject.h"

CPlayer::CPlayer(void)
{
	// TODO
	// 최초 상태 초기화
	// 이제 주상태 / 보조상태를 통해서 모션들을 분간해야함
	ZeroMemory(&_direction, sizeof(D3DXVECTOR3));

	_state.main = EMainState::NORMAL;
	_state.sub = ESubState::WAIT;

	_status.hp = 4000;
	_status.MinAtk = 400;
	_status.MaxAtk = 600;
	_status.perDef = 30;
	_status.perAtkCri = 20;
	_status.perAtkCriDmg = 150;
	_status.realAtk = CreateIntRandomValue(_status.MinAtk, _status.MaxAtk);
	_status.perAtkAcc = 90;
	_status.lastAtkDelayTime = 0.5f;
}

CPlayer::~CPlayer(void)
{
	SAFE_DELETE(_skinnedMesh);
}

void CPlayer::init(void)
{

	// 초기화
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 20.0f, 0.01f, 20.0f);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;

	_skinnedMesh = this->CreateSkinnedMesh();
	_skinnedMesh->setScale(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	_skinnedMesh->setRotation(D3DXVECTOR3(0.0f, -90.0f, 0.0f));
	_skinnedMesh->setShadowEnable(true);
	_skinnedMesh->setShadowMatrix(worldMatrix);
	//_skinnedMesh->setDebugEnable(true, EDebugType::SPHERE);
	_skinnedMesh->setTimeScale(0.8f);
	this->addChildObject(_skinnedMesh);

	/*auto offset = _skinnedMesh->getFollowPosition() - this->getPosition();
	_skinnedMesh->moveByYAxis(offset.y);*/

	_damageSkin = new CTeraDMFont();
	_damageSkin->setScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	this->addChildObject(_damageSkin);

	_label = new CLabel(_textComboStack, 20);
	_label->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f - 40, 30.0f, 0.0f));


	_buffEffect = new CTeraEffect(L"Resources/Effekseers/PowerBuff3.efk");
	this->addChildObject(_buffEffect);

	_particleSystem = this->CreateParticleSystem();
	this->addChildObject(_particleSystem);
}

void CPlayer::update(void)
{
	CRenderObject::update();

	if (((CSceneObject*)(this->m_pParentObject))->getSceneName() == "MainScene"){
		if (_state.sub == ESubState::RUN) {
			_footTimer += GET_DELTA_TIME();
			if (_footTimer >= 0.5f) {
				_footTimer = 0.0f;
				char random[256] = "";
				sprintf(random, "Resources/Sounds/Player/Foot/Ostrich_Foot_Grass_%02d.wav", CreateIntRandomValue(1, 4));
				GET_SOUND_MANAGER()->setEffectsVolume(0.5f);
				PLAY_EFFECT_SOUND(random);
			}
		}
	}

	if (_status.hp <= 1500) {
		_status.hp = 4000;
		((CSceneObject*)this->m_pParentObject)->getTeraUI()->setHpPercent(-4000);
	}

	// 플레이어 y값 조절
	// {
	if (((MainScene*)(this->m_pParentObject))->getSceneName() == "MainScene") {
		auto playerPos = this->getPosition();
		playerPos.y = GET_MAP(GET_MAP_MANAGER()->getName())->getHeightMapY(playerPos);
		this->setPosition(playerPos);
	}
	else {
		auto playerPos = this->getPosition();
		playerPos.y = 4.0f;
		this->setPosition(playerPos);
	}
	
	// ------------------------------------ 상태 갱신

	if (_state.main == EMainState::NORMAL)
	{
		if (_state.sub == ESubState::WAIT)
		{
			if (!_isInWeapon)
			{
				//DO NOTHING
			}
			else if (_isInWeapon)
			{
				this->NormalWait();
			}
		}

		else if (_state.sub == ESubState::RUN)
		{
			this->NormalRun();
		}
	}

	else if (_state.main == EMainState::ATK)
	{
		_atkWaitCount += GET_DELTA_TIME();
		_isInWeapon = false;
		_target = nullptr;

		if (_atkWaitCount >= 800 && _state.sub == ESubState::WAIT)
		{
			_atkWaitCount = 0;
			_state.main = EMainState::NORMAL;
			_state.sub = ESubState::WAIT;
			this->InWeapon();
		}

		else
		{
			if (_state.sub == ESubState::WAIT)
			{
				this->AttackWait();
			}

			else if (_state.sub == ESubState::RUN)
			{
				this->AtkRun();
			}
		}
	}

	else if (_state.main == EMainState::ISATK || _state.main == EMainState::STINGERBLADE
		|| _state.main == EMainState::GAIACRUSH || _state.main == EMainState::CUTTINGSLASH || _state.main == EMainState::BEATTACK)
	{
		_atkWaitCount = 0;
	}

	////////////////////////////  충돌판정 Player -> Monster;
	if (_state.main == EMainState::ISATK
		|| _state.main == EMainState::CUTTINGSLASH
		|| _state.main == EMainState::GAIACRUSH
		|| _state.main == EMainState::STINGERBLADE)
	{
		// 메인씬
		if (((MainScene*)(this->m_pParentObject))->getSceneName() == "MainScene") {
			auto pMWeapon = _skinnedMesh->getFinalMainWeaponBoundingSphereW();
			auto pSWeapon = _skinnedMesh->getFinalSubWeaponBoundingSphereW();

			for (auto &monster : GET_MONSTER()->getAllMonsterList()) {
				auto mBSphere = monster->getSkinnedMesh()->getFinalBoundingSphere();
				auto mMSphere = monster->getSkinnedMesh()->getFinalMainWeaponBoundingSphereW();

				if (isIntersectSphere(pMWeapon, mBSphere)
					|| isIntersectSphere(pMWeapon, mMSphere)
					|| isIntersectSphere(pSWeapon, mBSphere)
					|| isIntersectSphere(pSWeapon, mMSphere))
				{
					if (_target == nullptr) {
						_target = monster;
						auto tDamage = CreateIntRandomValue(_status.MinAtk, _status.MaxAtk);

						switch (_state.main)
						{
						case EMainState::ISATK:	// 평타
							monster->BeAttacked(this, tDamage);			break;
						case EMainState::CUTTINGSLASH:	// 스킬1
							monster->BeAttacked(this, tDamage * 2.0f);	break;
						case EMainState::GAIACRUSH:		// 스킬2
							monster->BeAttacked(this, tDamage * 2.5f);	break;
						case EMainState::STINGERBLADE:	// 스킬3
							monster->BeAttacked(this, tDamage * 3.0f);	break;
						}

						break; // for문 탈출 (이미 공격판정이 났기때문에 포문벗어남)
					}
				}
			}
		}
		else {            ///////////////////// 보스맵 판정
			auto pSphere = _skinnedMesh->getFinalMainWeaponBoundingSphereW();
			auto pSphere2 = _skinnedMesh->getFinalSubWeaponBoundingSphereW();

			// 몬스터 리스트를 탐색하면서 베르고스를 찾는다.
			auto monsterList = GET_MONSTER()->getAllMonsterList();
			auto monsterIter = std::find_if(monsterList.begin(),
				monsterList.end(),
				[=](CMonster* monster) -> bool
			{
				return monster->getMonsterName() == "M_Vergos";
			});

			// 플레이어 -> 몬스터 공격 판정
			// 플레이어 공격이 몬스터에 닿았는가?
			auto mSphere = (*monsterIter)->getSkinnedMeshBoss()->getFinalBoundingSphere();
			auto mSphere1 = (*monsterIter)->getSkinnedMeshBoss()->getFinalMainWeaponBoundingSphereW();
			auto mSphere2 = (*monsterIter)->getSkinnedMeshBoss()->getFinalSubWeaponBoundingSphereW();
			auto mSphere3 = (*monsterIter)->getSkinnedMeshBoss()->getFinalThirdWeaponBoundingSphereW();

			if (isIntersectSphere(pSphere, mSphere) ||
				isIntersectSphere(pSphere2, mSphere) ||
				isIntersectSphere(pSphere, mSphere1) ||
				isIntersectSphere(pSphere2, mSphere1) ||
				isIntersectSphere(pSphere, mSphere2) ||
				isIntersectSphere(pSphere2, mSphere2) ||
				isIntersectSphere(pSphere, mSphere3) ||
				isIntersectSphere(pSphere2, mSphere3))
			{
				if (_target == nullptr) {
					_target = (*monsterIter);

					auto damage = CreateIntRandomValue(_status.MinAtk, _status.MaxAtk);

					switch (_state.main)
					{
					case EMainState::ISATK:	// 평타
						{
							(*monsterIter)->BeAttacked(this, damage);
							break;
						}
					case EMainState::CUTTINGSLASH:	// 스킬1
						{
							auto realDamage = damage * 2.0f;
							(*monsterIter)->BeAttacked(this, realDamage);
							break;
						}
					case EMainState::GAIACRUSH:		// 스킬2
						{
							auto realDamage = damage * 2.5f;
							(*monsterIter)->BeAttacked(this, damage * 2.5f);
							break;
						}
						
					case EMainState::STINGERBLADE:	// 스킬3
						{
							auto realDamage = damage * 3.0f;
							(*monsterIter)->BeAttacked(this, damage * 3.0f);
							break;
						}
					}
				}
			}
		}
	}


	//--------------------------- 입력 받는 부분
	// 마우스 
	if (GET_CAMERA()->getFollowObjectEnable()) {

		// 이동 조작 들어오면
		if (IS_KEY_DOWN(DIK_W)
			|| IS_KEY_DOWN(DIK_A)
			|| IS_KEY_DOWN(DIK_S)
			|| IS_KEY_DOWN(DIK_D)) {
			_atkWaitCount = 0;
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH
				&& _state.main != EMainState::GAIACRUSH && _state.main != EMainState::STINGERBLADE
				&& !_isPlayWeapon && _state.main != EMainState::BEATTACK &&_state.main != EMainState::TENACITY)
			{
				this->moveByZAxis(GET_DELTA_TIME() * 30.f);
				_state.sub = ESubState::RUN;
			}
		}
		else {
			_state.sub = ESubState::WAIT;
		}

		bool isForward = false;
		bool isBackward = false;
		if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH
			&& _state.main != EMainState::GAIACRUSH && _state.main != EMainState::STINGERBLADE
			&& !_isPlayWeapon && _state.main != EMainState::BEATTACK && _state.main != EMainState::TENACITY)
		{
			if (IS_KEY_DOWN(DIK_W)) {
				D3DXVec3Cross(&_direction, &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &GET_CAMERA()->getRightDirection());
				D3DXVec3Normalize(&_direction, &_direction);
				this->rotateByDirection(_direction);
				isForward = true;
			}
			else if (IS_KEY_DOWN(DIK_S)) {
				D3DXVec3Cross(&_direction, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &GET_CAMERA()->getRightDirection());
				D3DXVec3Normalize(&_direction, &_direction);
				this->rotateByDirection(_direction);
				isBackward = true;
			}

			if (IS_KEY_DOWN(DIK_D)) {
				if (isForward) {
					D3DXMATRIXA16 rotationMatrix;
					D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(45.0f));
					D3DXVec3TransformCoord(&_direction, &_direction, &rotationMatrix);
					this->rotateByDirection(_direction);
				}
				else if (isBackward) {
					D3DXMATRIXA16 rotationMatrix;
					D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(-45.0f));
					D3DXVec3TransformCoord(&_direction, &_direction, &rotationMatrix);
					this->rotateByDirection(_direction);
				}
				else {
					_direction = GET_CAMERA()->getRightDirection();
					this->rotateByDirection(_direction * 1.0f);
				}
			}
			else if (IS_KEY_DOWN(DIK_A)) {
				if (isForward) {
					D3DXMATRIXA16 rotationMatrix;
					D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(-45.0f));
					D3DXVec3TransformCoord(&_direction, &_direction, &rotationMatrix);
					this->rotateByDirection(_direction);
				}
				else if (isBackward) {
					D3DXMATRIXA16 rotationMatrix;
					D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(45.0f));
					D3DXVec3TransformCoord(&_direction, &_direction, &rotationMatrix);
					this->rotateByDirection(_direction);
				}
				else {
					_direction = GET_CAMERA()->getRightDirection();
					this->rotateByDirection(_direction * -1.0f);
				}
			}
		}


		// 무기 넣기 -> 평시대기 Loop
		if (IS_KEY_PRESSED(DIK_H)) {
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH && _state.main != EMainState::GAIACRUSH
				&& _state.main != EMainState::STINGERBLADE && _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::GAIACRUSH;
				_skinnedMesh->PlayAnimation("gaiaCrush01", false, false, [=](const std::string &animName)->void {
					_skinnedMesh->PlayAnimation("gaiaCrush02", false, false, [=](const std::string &animName)->void {
						this->moveByZAxis(13.5f);
						_skinnedMesh->PlayAnimation("gaiaCrush03", false, false, [=](const std::string &animName)->void {
							_state.main = EMainState::ATK;
						});
						_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
							if (animName == "gaiaCrush03" && percent >= 0.3f && percent <= 0.4f) {
								PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_FlatBlade_Explosion.wav");
							}
						});
					});
				});
				_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
					if (animName == "gaiaCrush01" && percent >= 0.5f && percent <= 0.6f) {
						PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_FlatBlade_Casting.wav");
					}
				});
			}
		}
		else if (IS_KEY_PRESSED(DIK_J)) {
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH && _state.main != EMainState::GAIACRUSH
				&& _state.main != EMainState::STINGERBLADE && _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::CUTTINGSLASH;
				_target = nullptr;

				_skinnedMesh->PlayAnimation("CuttingSlash", false, false, [=](const std::string &animName)->void {
					this->moveByZAxis(34.0f);
					_state.main = EMainState::ATK;
				});

				_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
					if (percent >= 0.2f && percent <= 0.3f) {
						PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_CuttingSlash_Casting_00.wav");
					}
					else if (percent >= 0.3f && percent <= 0.4f) {
						PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_CuttingSlash_Casting_01.wav");
					}
					else if (percent >= 0.55f && percent <= 0.65f) {
						PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_CuttingSlash_Explosion.wav");
					}
				});
			}
		}
		else if (IS_KEY_PRESSED(DIK_K)) {
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH && _state.main != EMainState::GAIACRUSH
				&& _state.main != EMainState::STINGERBLADE && _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::STINGERBLADE;
				_target = nullptr;
				_skinnedMesh->PlayAnimation("StingerBlade", false, false, [=](const std::string &animName)->void {
					this->moveByZAxis(34.0f);
					_state.main = EMainState::ATK;
				});
				PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_StingerBlade_Casting.wav");

				_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
					if (animName == "StingerBlade" && percent >= 0.4f && percent <= 0.6f) {
						PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_StingerBlade_Shot.wav");
					}
					else if (animName == "StingerBlade" && percent >= 0.7 && percent <= 0.9f) {
						PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_StingerBlade_Explosion.wav");
					}
				});
			}
		}
		/////////////////////////////// 버프
		else if (IS_KEY_PRESSED(DIK_L)) {
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH && _state.main != EMainState::GAIACRUSH
				&& _state.main != EMainState::STINGERBLADE && _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::TENACITY;
				_target = nullptr;

				_buffEffect->playEffeckseer(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				_buffEffect->setScaleEffekseer(70.0f, 70.0f, 70.0f);
				_skinnedMesh->PlayAnimation("Victory", false, false, [=](const std::string &animName)->void
				{
					_state.main = EMainState::ATK;
				});
				PLAY_EFFECT_SOUND("Resources/Sounds/Player/Slayer/Slayer_Tenacity_Casting.wav");
				PLAY_EFFECT_SOUND("Resources/Sounds/Player/Voice/Roar.wav"); 
			}
		}

		if (IS_MOUSE_DOWN((int)EMouseInput::LEFT_BUTTON)) {
			if (_state.sub == ESubState::WAIT && _state.main != EMainState::CUTTINGSLASH
				&& _state.main != EMainState::GAIACRUSH && _state.main != EMainState::STINGERBLADE &&  _state.main != EMainState::BEATTACK 
				&& _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::ISATK;
			}
			this->NormalAtk();
		}
	}


	// 디버그용 텍스트
	std::string isCom = "";
	_isPlayingCombo ? isCom = "true" : isCom = "false";
	sprintf(_textComboStack, "stack:%d  isCom:%s  state :%d atkwait :%f", _comboStack, isCom.c_str(), (int)_state.main,_atkWaitCount);

	if (_label->getVisible()) {
		_label->setString(_textComboStack);
	}

	// 디버그 텍스트 숨기기
	if (IS_KEY_PRESSED(DIK_B)) {
		_label->getVisible() ? _label->setVisible(false) : _label->setVisible(true);
	}
	
}
void CPlayer::NormalAtk(void)
{
	// 더미루트가 이동이 끝난만큼 이동해줘야함.
	// PERCENT가 0.0이면 빠르게 공격하긴하나 부들거림
	if (!_isPlayingCombo && _state.main == EMainState::ISATK && _state.sub == ESubState::WAIT) {
		_isPlayingCombo = true;
		_target = nullptr;
		if (_comboStack == 0) {
			_skinnedMesh->PlayAnimation("combo1", false, false, [=](const std::string &animName)->void {
				this->moveByZAxis(7.5f);
				_skinnedMesh->PlayAnimation("combo1R", false, false, [=](const std::string &animName)->void {
					//DO NOTHING
					//_state.main = EMainState::ATK;
					//_comboStack = 0;
				});
				_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
					//0.5에서 0.6사이에 펄스일때만 트루로 해준다 그리고 밑에 동작이 끝날때쯤까지 안들어오면 펄스로 바꿔줌
					if (percent >= 0.5) {
						_isPlayingCombo = false;
						_comboStack = 1;
					}

					if (percent >= 0.8)
					{
						_state.main = EMainState::ATK;
						_comboStack = 0;
					}
				});
			});
			/*_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
					printf("string name: %s, percent : %f", animName, percent);
			});*/
		}
		if (_comboStack == 1) {
			_skinnedMesh->PlayAnimation("combo2", false, false, [=](const std::string &animName)->void {
				this->moveByZAxis(7.5f);
				_skinnedMesh->PlayAnimation("combo2R", false, false, [=](const std::string &animName)->void {
					//DO NOTHING
				});

				_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {

					if (percent < 0.8) {
						_isPlayingCombo = false;
						_comboStack = 2;
					}

					if (percent >= 0.8)
					{
						_state.main = EMainState::ATK;
						_comboStack = 0;
					}

				});
			});
		}
		if (_comboStack == 2) {
			_skinnedMesh->PlayAnimation("combo3", false, false, [=](const std::string &animName)->void {
				this->moveByZAxis(7.5f);
				_skinnedMesh->PlayAnimation("combo3R", false, false, [=](const std::string &animName)->void {
					//DO NOTHING
					/*_state.main = EMainState::ATK;
					_comboStack = 0;*/
				});
				_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
					if (percent < 0.8) {
						_isPlayingCombo = false;
						_comboStack = 3;
					}

					if (percent >= 0.8)
					{
						_state.main = EMainState::ATK;
						_comboStack = 0;
					}

				});
			});
		}
		if (_comboStack == 3) {
			_skinnedMesh->PlayAnimation("combo4", false, false, [=](const std::string &animName)->void {
				this->moveByZAxis(7.5f);
				_skinnedMesh->PlayAnimation("AtkWait", false, false, [=](const std::string &animName)->void {
					//DO NOTHING
					/*_state.main = EMainState::ATK;
					_comboStack = 0;*/
				});
				_skinnedMesh->setCallback([=](const std::string &animName, float percent)->void {
					if (percent < 0.8) {
						_isPlayingCombo = false;
						_comboStack = 0;
					}

					if (percent >= 0.8)
					{
						_state.main = EMainState::ATK;
						_comboStack = 0;
					}

				});
			});
		}
	}
}

void CPlayer::AtkRun(void)
{
	_skinnedMesh->PlayAnimation("AtkRun", false, false, [=](const std::string &animName)->void {
		_skinnedMesh->PlayAnimation("AtkWait", true);
	});
}

void CPlayer::Death(void)
{
	_skinnedMesh->PlayAnimation("death", false, false, [=](const std::string &animName)->void {
		_skinnedMesh->PlayAnimation("deathWait", true);
	});
}

void CPlayer::InWeapon(void)
{
	_skinnedMesh->PlayAnimation("InWeapon", false, false, [=](const std::string &animName)->void {
		_isInWeapon = true;
		_isPlayWeapon = false;
	});
	if (!_isPlayWeapon)
	{
		_isPlayWeapon = true;
	}

}

void CPlayer::OutWeapon(void)
{
	_skinnedMesh->PlayAnimation("OutWeapon", false, false, [=](const std::string &animName)->void {
		_skinnedMesh->PlayAnimation("AtkWait", true);
	});
}

void CPlayer::BeAttacked(CMonster * target, int damage)
{
	_comboStack = 0;
	_isPlayingCombo = false;
	if (_state.main != EMainState::BEATTACK)
	{
		auto realDmg = damage * (100 - _status.perDef) / 100;
		_status.hp -= realDmg;
		((CSceneObject*)this->m_pParentObject)->getTeraUI()->setHpPercent(realDmg);

		char soundPath[256];
		sprintf(soundPath, "Resources/Sounds/Player/NormalAtk/Damage00_%02d.wav", CreateIntRandomValue(0, 5));
		PLAY_EFFECT_SOUND(soundPath);
		_damageSkin->damageCalculate(realDmg, D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f+15, GET_WINDOW_SIZE().cy / 2.0f+15, 0));

		_skinnedMesh->PlayAnimation("sReaction", false, false, [=](const std::string &animName)->void {
			_state.main = EMainState::ATK;

		});
	}
	_atkWaitCount = 0;
	_state.main = EMainState::BEATTACK;
}

void CPlayer::NormalRun(void)
{
	_skinnedMesh->PlayAnimation("NormalRun", true);
}

void CPlayer::NormalWalk(void)
{
	_skinnedMesh->PlayAnimation("NormalWalk", true);
}
//=====================함수 추가
void CPlayer::NormalWait(void)
{
	_skinnedMesh->PlayAnimation("NormalWait", true);
}

void CPlayer::AttackWait(void)
{
	_skinnedMesh->PlayAnimation("AtkWait", true);
}

void CPlayer::doHitMonster(void)
{

}

CSkinnedMesh * CPlayer::CreateSkinnedMesh(void)
{
	CSkinnedMesh::STParameters parameters = {
		"Resources/Meshes/Player/Player.x",
		"Resources/Effects/PlayerEffect.fx",
		"Dummy_root",
		"TwoHand17",
		"TwoHand17",
		"none"
	};

	return new CSkinnedMesh(parameters, SkinnedType::Player);
}

CParticleSystem * CPlayer::CreateParticleSystem(void)
{
	CParticleSystem::STParameters parameters = {
		"Resources/Textures/test2.tga",
		2048,
		1000
	};
	return new CParticleSystem(parameters);
}
