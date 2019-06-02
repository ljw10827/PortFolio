#include "MGhillieDhu.h"
#include "../../Global/Function/GlobalFunction.h"
#include "../Monster/CMonsterFactory.h"
// TODO
MGhillieDhu::MGhillieDhu(const std::string & monsterName)
	:
	CMonster(monsterName)
{

}

MGhillieDhu::~MGhillieDhu(void)
{
	CMonster::~CMonster();
}

void MGhillieDhu::init(void)
{
	CMonster::init();
	this->setScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	_moveSpeed = CreateFloatRandomValue(13.0f, 15.0f);

	_status.hp = CreateIntRandomValue(4000, 5000);
	_status.maxAtk = CreateIntRandomValue(180, 200);
	_status.minAtk = CreateIntRandomValue(120, 140);
	_status.perAtkAcc = 0;
	_status.perAtkCri = 0;
	_status.perAtkDmg = 0;
	_status.PerDef = CreateIntRandomValue(10, 15);

	// ÃÊ±âÈ­
	D3DXMATRIXA16 shadowMatrix;
	D3DXMatrixScaling(&shadowMatrix, 40, 0.01f, 40);

	D3DXMATRIXA16 translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, 0.0f, -20.0f, 0.0f);

	D3DXMATRIXA16 worldMatrix = shadowMatrix * translationMatrix;
	_skinnedMesh->setShadowMatrix(worldMatrix);
}

void MGhillieDhu::update(void)
{
	CMonster::update();

	auto stPos = this->getPosition();
	if (this->getPosition().x > -129.0f &&this->getPosition().x < 87.0f &&
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
			stPos.z = 445.0f;
			this->setPosition(stPos);
		}
	}

	if (this->getPosition().x > -172.0f && this->getPosition().x < -30.0f &&
		this->getPosition().z > -295.0f && this->getPosition().z < -176.0f)
	{
		if (this->getPosition().x < -172.0)
		{
			stPos.x = -172.0;
			this->setPosition(stPos);
		}
		if (this->getPosition().x > -30.0f)
		{
			stPos.x = -30.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z < -295.0f)
		{
			stPos.z = -295.0f;
			this->setPosition(stPos);
		}
		if (this->getPosition().z > -176.0f)
		{
			stPos.z = -176.0f;
			this->setPosition(stPos);
		}
	}
}

void MGhillieDhu::doDrawObject(void)
{
	CMonster::doDrawObject();
}

void MGhillieDhu::NormalAtk(void)
{
	_state = EState::ISATTACKING;

	char temp[256] = "";
	sprintf(temp, "Resources/Sounds/Monster/M_GhillieDhu/Atk%02d.wav", CreateIntRandomValue(1, 3));
	PLAY_EFFECT_SOUND(temp);

	_skinnedMesh->PlayAnimation("Atk02", false, false, [=](const std::string &animName)->void {
		this->moveByZAxis(-8.1f);
		_state = EState::ATK;
	});
}

void MGhillieDhu::BeAttacked(CPlayer * target, int damage)
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