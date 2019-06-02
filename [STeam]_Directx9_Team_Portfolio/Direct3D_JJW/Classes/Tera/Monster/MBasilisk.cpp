#include "MBasilisk.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../../Global/Utility/Manager/CInputManager.h"
// TODO
MBasilisk::MBasilisk(const std::string & monsterName)
	:
	CMonster(monsterName),
	_phaseState(EPhase::PHASE00)
{
	
}

MBasilisk::~MBasilisk(void)
{
	CMonster::~CMonster();
}

void MBasilisk::init(void)
{
	CMonster::init();
	_moveSpeed = 20.0f;

	_status.hp = CreateIntRandomValue(8000, 12000);
	_status.maxAtk = CreateIntRandomValue(350, 400);
	_status.minAtk = CreateIntRandomValue(250, 350);
	_status.perAtkAcc = 0;
	_status.perAtkCri = 0;
	_status.perAtkDmg = 0;
	_status.PerDef = CreateIntRandomValue(15, 25);

	// 지워야함 테스트
	//this->setPosition(D3DXVECTOR3(0, 0.0f, 0));

	// 초기화
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 100.0f, 0.01f, 100.0f);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMesh->setShadowMatrix(worldMatrix);
}

void MBasilisk::update(void)
{
	CMonster::update();

	auto stPos = this->getPosition();
	if (this->getPosition().x < -110)
	{
		stPos.x = -110;
		this->setPosition(stPos);
	}
	if (this->getPosition().x > 187)
	{
		stPos.x = 187;
		this->setPosition(stPos);
	}
	if (this->getPosition().z < -48)
	{
		stPos.z = -48;
		this->setPosition(stPos);
	}
	if (this->getPosition().z > 148)
	{
		stPos.z = 148;
		this->setPosition(stPos);
	}




	/////////////////////// ------------ 페이즈
	switch (_phaseState)
	{
	case MBasilisk::EPhase::PHASE00:
		this->Phase00();
		break;
	case MBasilisk::EPhase::PHASE01:
		this->Phase01();
		break;
	case MBasilisk::EPhase::PHASE02:
		this->Phase02();
		break;
	}

}

void MBasilisk::doDrawObject(void)
{
	CMonster::doDrawObject();
}

// 페이즈 0 = 평소상태
void MBasilisk::Phase00(void)
{
}

//페이즈 1 = 피가 30프로이상 깍였을때
void MBasilisk::Phase01(void)
{
}

//페이즈 2 = 피가 30프로이하로 남았을때
void MBasilisk::Phase02(void)
{
}

void MBasilisk::NormalAtk()
{
	_state = EState::ISATTACKING;
	if (CreateIntRandomValue(0, 100) > 60) {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/M_Basilisk/Atk01.wav");
	}
	else {
		PLAY_EFFECT_SOUND("Resources/Sounds/Monster/M_Basilisk/Atk02.wav");
	}

	_skinnedMesh->PlayAnimation("Atk01", false, false, [=](const std::string &animName)->void {
		_state = EState::ATK;
	});
}


void MBasilisk::BeAttacked(CPlayer * target, int damage)
{
	if (_state != EState::REMOVE && _state != EState::BEATTACKED) {
		CMonster::BeAttacked(target, damage);

		auto animList = _skinnedMesh->getAnimationNameList();
		std::string animName = "";

		for (auto iterator : animList) {
			if (iterator == "AggroChange" || iterator == "Stun") {
				animName = iterator;
			}
			else {
				animName = "none";
			}
		}

		if (animName != "none") {
			_skinnedMesh->PlayAnimation(animName, false, false, [=](const std::string &animName)->void {
				_state = EState::BEATTACKED;
			});
		}
		else {
			_state = EState::BEATTACKED;
		}
	}

}