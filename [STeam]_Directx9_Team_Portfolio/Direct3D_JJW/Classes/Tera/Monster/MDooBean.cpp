#include "MDooBean.h"
#include "../../Global/Function/GlobalFunction.h"

#include "CMonsterFactory.h"

// TODO
MDooBean::MDooBean(const std::string & monsterName)
	:
	CMonster(monsterName)
{

}

MDooBean::~MDooBean(void)
{
	CMonster::~CMonster();
}

void MDooBean::init(void)
{
	CMonster::init();
	_moveSpeed = CreateFloatRandomValue(5.0f, 7.0f);

	_status.hp = CreateIntRandomValue(1000, 1500);
	_status.maxAtk = CreateIntRandomValue(30, 40);
	_status.minAtk = CreateIntRandomValue(20, 30);
	_status.perAtkAcc = 0;
	_status.perAtkCri = 0;
	_status.perAtkDmg = 0;
	_status.PerDef = CreateIntRandomValue(0, 5);

	// ÃÊ±âÈ­
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 10, 0.01f, 10);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMesh->setShadowMatrix(worldMatrix);
}

void MDooBean::update(void)
{
	CMonster::update();

	auto stPos = this->getPosition();
	if (this->getPosition().x > -447.0f &&this->getPosition().x < 222.0f &&
		this->getPosition().z > 337.0f && this->getPosition().z < 453.0f)
	{
		if (this->getPosition().x < -447.0f)
		{
			stPos.x = -447.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().x > 222.0f)
		{
			stPos.x = 222.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z < 337.0f)
		{
			stPos.z = 337.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z > 453.0f)
		{
			stPos.z = 453.0f;
			this->setPosition(stPos);
		}
	}

	if (this->getPosition().x > -113.0f && this->getPosition().x < 190.0f &&
		this->getPosition().z > -50.0f && this->getPosition().z < 150.0f)
	{
		if (this->getPosition().x > 190.0f)
		{
			stPos.x = 190.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().x < -113.0f)
		{
			stPos.x = -113.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z > 150.0f)
		{
			stPos.z = 150.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z < -50.0f)
		{
			stPos.z = -50.0f;
			this->setPosition(stPos);
		}
	}
}

void MDooBean::doDrawObject(void)
{
	CMonster::doDrawObject();
}

void MDooBean::NormalAtk(void)
{
	_state = EState::ISATTACKING;

	_skinnedMesh->PlayAnimation("atk01", false, false, [=](const std::string &animName)->void {
		_state = EState::ATK;
	});
}

void MDooBean::BeAttacked(CPlayer * target, int damage)
{
	if (_state != EState::REMOVE && _state != EState::BEATTACKED) {
		CMonster::BeAttacked(target, damage);
		printf("true\n");
		char soundPath[256];
		sprintf(soundPath, "Resources/Sounds/Monster/M_DooBean/%02d.wav", CreateIntRandomValue(1, 3));

		PLAY_EFFECT_SOUND(soundPath);

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