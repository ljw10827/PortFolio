#include "CPlayer.h"
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
#include "../../Global/Utility/Object/CParticleSystem.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../../Tera/Monster/CMonsterFactory.h"
#include "../Monster/MBasilisk.h"
#include "../Map/CTeraMapManager.h"
#include "../Monster/CMonster.h"
#include "../TeraEffect/CTeraEffect.h"
#include "../TeraScene/MainScene.h"


CPlayer::CPlayer(void)
{
	// TODO
	// 최초 상태 초기화
	// 이제 주상태 / 보조상태를 통해서 모션들을 분간해야함
	ZeroMemory(&_direction, sizeof(D3DXVECTOR3));

	_state.main = EMainState::NORMAL;
	_state.sub = ESubState::WAIT;

	_status.hp = 3000;
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
	D3DXMatrixScaling(&shadowMatrix, 30.0f, 0.01f, 30.0f);

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
	this->addChildObject(_damageSkin);


	_label = new CLabel(_textComboStack, 20);
	_label->setPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f - 40, 30.0f, 0.0f));
	this->addChildObject(_label);

	_buffEffect = new CTeraEffect(L"Resources/Effekseers/PowerBuff3.efk");
	this->addChildObject(_buffEffect);

	_particleSystem = this->CreateParticleSystem();
	this->addChildObject(_particleSystem);

}

void CPlayer::update(void)
{
	CRenderObject::update();

	// 파티클 ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ
	if (IS_KEY_DOWN(DIK_1)) {
		_particleSystem->StartParticleAnimation(0.0f);
	}
	else if (IS_KEY_PRESSED(DIK_SPACE)) {
		_particleSystem->StartParticleAnimation(2.0f);
	}


	printf("pos : %f, %f, %f\n", this->getPosition().x, this->getPosition().y, this->getPosition().z);
	// 플레이어 발자국 사운드

	if (_state.sub == ESubState::RUN) {
		_footTimer += GET_DELTA_TIME();
		if (_footTimer >= 0.5f) {
			_footTimer = 0.0f;
			int random = CreateIntRandomValue(1, 4);
			GET_SOUND_MANAGER()->setEffectsVolume(0.5f);

			switch (random) {
			case 1:
				PLAY_EFFECT_SOUND("Resources/Sounds/Player/Foot/Ostrich_Foot_Grass_01.wav");
				break;
			case 2:
				PLAY_EFFECT_SOUND("Resources/Sounds/Player/Foot/Ostrich_Foot_Grass_02.wav");
				break;
			case 3:
				PLAY_EFFECT_SOUND("Resources/Sounds/Player/Foot/Ostrich_Foot_Grass_03.wav");
				break;
			case 4:
				PLAY_EFFECT_SOUND("Resources/Sounds/Player/Foot/Ostrich_Foot_Grass_04.wav");
				break;
			}

		}
	}

	// 플레이어 y값 조절
	// {
	auto playerPos = this->getPosition();
	playerPos.y = GET_MAP(GET_MAP_MANAGER()->getName())->getHeightMapY(playerPos);
	this->setPosition(playerPos);



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
		|| _state.main == EMainState::GAIACRUSH || _state.main == EMainState::CUTTINGSLASH)
	{
		_atkWaitCount = 0;
	}





	//--------------------------- 입력 받는 부분
	// 마우스 
	if (GET_CAMERA()->getFollowObjectEnable()) {
		// 점프
		if (IS_KEY_PRESSED(DIK_SPACE)) {
			this->Jump();
		}

		if (IS_KEY_DOWN(DIK_W)
			|| IS_KEY_DOWN(DIK_A)
			|| IS_KEY_DOWN(DIK_S)
			|| IS_KEY_DOWN(DIK_D)) {
			_atkWaitCount = 0;
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH
				&& _state.main != EMainState::GAIACRUSH && _state.main != EMainState::STINGERBLADE
				&& !_isPlayWeapon && _state.main != EMainState::BEATTACK )
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
			&& !_isPlayWeapon && _state.main != EMainState::BEATTACK)
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
						this->moveByZAxis(12.0f);
						_skinnedMesh->PlayAnimation("gaiaCrush03", false, false, [=](const std::string &animName)->void {
							_state.main = EMainState::ATK;
						});
					});
				});
			}
		}
		else if (IS_KEY_PRESSED(DIK_J)) {
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH && _state.main != EMainState::GAIACRUSH
				&& _state.main != EMainState::STINGERBLADE && _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::CUTTINGSLASH;
				_skinnedMesh->PlayAnimation("CuttingSlash", false, false, [=](const std::string &animName)->void
				{
					this->moveByZAxis(34.0f);
					_state.main = EMainState::ATK;
				});
			}
		}
		else if (IS_KEY_PRESSED(DIK_K)) {
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH && _state.main != EMainState::GAIACRUSH
				&& _state.main != EMainState::STINGERBLADE && _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::STINGERBLADE;
				_skinnedMesh->PlayAnimation("StingerBlade", false, false, [=](const std::string &animName)->void
				{
					this->moveByZAxis(34.0f);
					_state.main = EMainState::ATK;
				});
			}
		}

		else if (IS_KEY_PRESSED(DIK_L)) {
			if (_state.main != EMainState::ISATK && _state.main != EMainState::CUTTINGSLASH && _state.main != EMainState::GAIACRUSH
				&& _state.main != EMainState::STINGERBLADE && _state.main != EMainState::TENACITY)
			{
				_state.main = EMainState::TENACITY;

				_buffEffect->playEffeckseer(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				_buffEffect->setScaleEffekseer(70.0f, 70.0f, 70.0f);
				_skinnedMesh->PlayAnimation("Angry", false, false, [=](const std::string &animName)->void
				{
					_state.main = EMainState::ATK;
				});
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

void CPlayer::Jump(void)
{
	_isJumpLoop = true;
	_jumpSpeed = 28.f;

	_skinnedMesh->PlayAnimation("JumpStart", false, false, [=](const std::string &animName)->void {
		_skinnedMesh->PlayAnimation("JumpLoop", false, false, [=](const std::string &animName)->void {
			_skinnedMesh->PlayAnimation("JumpEnd", false, false, [=](const std::string &animName)->void {
				_skinnedMesh->PlayAnimation("NormalWait", true);
			});
		});
	});
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
	_isPlayingCombo = false;
	_comboStack = 0;
	if (_state.main != EMainState::BEATTACK)
	{
		_target = target;
		auto realDmg = damage * (100 - _status.perDef) / 100;
		_status.hp -= realDmg;

		((MainScene*)(this->m_pParentObject))->getTeraUI()->setHpPercent(realDmg);

		char soundPath[256];
		sprintf(soundPath, "Resources/Sounds/Player/NormalAtk/Damage00_%02d.wav", CreateIntRandomValue(0, 5));
		PLAY_EFFECT_SOUND(soundPath);
		//_damageSkin->damageCalculate(realDmg, D3DXVECTOR3(GET_WINDOW_SIZE().cx / 2.0f, GET_WINDOW_SIZE().cy / 2.0f, 0));

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
		250
	};
	return new CParticleSystem(parameters);
}
