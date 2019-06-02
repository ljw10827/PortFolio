#include "MArgass.h"
#include "../../Global/Function/GlobalFunction.h"
#include "CMonsterFactory.h"
// TODO
MArgass::MArgass(const std::string & monsterName)
	:
	CMonster(monsterName)
{

}

MArgass::~MArgass(void)
{
	CMonster::~CMonster();
}

void MArgass::init(void)
{
	CMonster::init();
	_moveSpeed = CreateFloatRandomValue(10.0f, 12.0f);

	_status.hp = CreateIntRandomValue(1500, 2000);
	_status.maxAtk = CreateIntRandomValue(40, 50);
	_status.minAtk = CreateIntRandomValue(30, 40);
	_status.perAtkAcc = 0;
	_status.perAtkCri = 0;
	_status.perAtkDmg = 0;
	_status.PerDef = CreateIntRandomValue(0, 7);

	// ÃÊ±âÈ­
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 70, 0.01f, 70);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMesh->setShadowMatrix(worldMatrix);
}

void MArgass::update(void)
{
	CMonster::update();

	auto stPos = this->getPosition();

	if (this->getPosition().x > -129.0f && this->getPosition().x < 87.0f &&
		this->getPosition().z > 278.0f && this->getPosition().z < 400.0f)
	{
		if (this->getPosition().x < -129.0f)
		{
			stPos.x = -129.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().x > 87.0f)
		{
			stPos.x = 87.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z < 278.0f)
		{
			stPos.z = 278.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z > 400.0f)
		{
			stPos.z = 400.0f;
			this->setPosition(stPos);
		}
	}

	if (this->getPosition().x > -172.0f && this->getPosition().x < 400.0f &&
		this->getPosition().z > 227.0f && this->getPosition().z < 400.0f)
	{
		if (this->getPosition().x < -172.0f)
		{
			stPos.x = -172.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().x > 400.0f)
		{
			stPos.x = 400.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z < 227.0f)
		{
			stPos.z = 227.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z > 400.0f)
		{
			stPos.z = 400.0f;
			this->setPosition(stPos);
		}
	}
	
}

void MArgass::NormalAtk(void)
{
	_state = EState::ISATTACKING;

	PLAY_EFFECT_SOUND("Resources/Sounds/Monster/M_Argass/Atk01.wav");

	_skinnedMesh->PlayAnimation("Atk01", false, false, [=](const std::string &animName)->void {
		this->moveByZAxis(-4.9f);
		_state = EState::ATK;
	});
}

void MArgass::BeAttacked(CPlayer * target, int damage)
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